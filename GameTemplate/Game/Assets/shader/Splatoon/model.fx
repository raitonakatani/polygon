/*!
 * @brief	シンプルなモデルシェーダー。
 */

struct Directionlight
{
	   // ディレクションライト用のデータ
    float3 dirDirection; // ライトの方向
    float3 dirColor; // ライトのカラー
};

struct Pointlight
{
    float3 ptPosition; //ポイントライトの位置。
    float3 ptColor; //ポイントライトのカラー。
    float ptRange; //ポイントライトの影響範囲。
};

struct Spotlight
{
    float3 spPosition; //スポットライトの位置。
    float3 spColor; //スポットライトのカラー。
    float spRange; //スポットライトの射出範囲。
    float3 spDirection; //スポットライトの射出方向。
    float spAngle; //スポットライトの射出角度。
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

cbuffer LightCb : register(b1)
{
    Directionlight directionlight;
    Pointlight pointlight;
    Spotlight spotlight;
    
    //アンビエントライト。
    float3 ambientLight; //環境光。
    
    float3 eyePos; //視点の位置。
	
    float uvscroll;
//    float uv;
    
    float4x4 mLVP;
};


////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn
{
    float4 pos : POSITION; //モデルの頂点座標。
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    float2 uv : TEXCOORD0; //UV座標。

    SSkinVSIn skinVert; //スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn
{
    float4 pos : SV_POSITION; //スクリーン空間でのピクセルの座標。
    float3 normal : NORMAL; //法線。
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    
    float2 uv : TEXCOORD0; //uv座標。
    float3 worldPos : TEXCOORD1;
    
    float3 normalInView : TEXCOORD2; //カメラ空間の法線
    float4 posInLVP : TEXCOORD3; // ライトビュースクリーン空間でのピクセルの座標

    float distToEye : TEXCOORD4; //視点との距離
};
///////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromPointLight(SPSIn psIn);
float3 CalcLigFromDirectionLight(SPSIn psIn);
float3 CalcLigFromSpotLight(SPSIn psIn);
float3 CalcRimLight(SPSIn psIn, float3 lightdirection, float3 lightcolor);


////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0); //アルベドマップ
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //ボーン行列。
//Texture2D<float4> g_shadowMap : register(t10); // シャドウマップ
TextureCube<float4> g_skyCubeMap : register(t10);
sampler g_sampler : register(s0); //サンプラステート。
static const int pattern[4][4] =
{
    { 0, 32, 8, 40 },
    { 48, 16, 56, 24 },
    { 12, 44, 4, 36 },
    { 60, 28, 52, 20 },
};

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    psIn.pos = mul(m, vsIn.pos);
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
	// 頂点法線をピクセルシェーダーに渡す。
    psIn.normal = normalize(mul(m, vsIn.normal)); //法線を回転させる。
    
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
    psIn.uv = vsIn.uv;
 
      //カメラ空間の法線を求める。
    psIn.normalInView = normalize(mul(mView, psIn.normal));
    
    psIn.posInLVP = mul(mLVP, float4(psIn.worldPos, 1.0f));

    // オブジェクトの座標をワールド行列の平行移動成分から取得する
    float4 objectPos = m[3];

    // オブジェクトの座標をカメラ座標系に変換する
    float4 objectPosInCamera = mul(mView, objectPos);

    // カメラからの距離を計算する
    psIn.distToEye = length(objectPosInCamera);

    return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}
/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}

/// <summary>
/// Phong鏡面反射光を計算する
/// <summary>
float3 CalcPhongSpecular(float3 normal, float3 worldPos, float3 lightDirection)
{
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);
    
    // 鏡面反射の強さを求める
    float t = saturate(dot(refVec, toEye));

    // 鏡面反射の強さを絞る
    t = pow(t, 2.0f) * 17.0f;

    //  鏡面反射光を求める
    float3 specularLig = directionlight.dirColor * t;
    return specularLig;
}
/// <summary>
/// ディレクションライトによる反射光を計算
/// </summary
/// <param name="psIn">ピクセルシェーダーからの入力。</param>
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
    // ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(directionlight.dirDirection, directionlight.dirColor, psIn.normal);

    //ディレクションライトによるリムライトを計算する。
    float3 rimDirection = CalcRimLight(psIn, directionlight.dirDirection, directionlight.dirColor);
    
    return diffDirection /*+ rimDirection*/; //+ specDirection
}
/// <summary>
/// ポイントライトによる反射光を計算
/// </summary>
/// <param name="psIn">ピクセルシェーダーに渡されている引数</param>
float3 CalcLigFromPointLight(SPSIn psIn)
{
    // このサーフェイスに入射しているポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - pointlight.ptPosition;

    // 正規化して大きさ1のベクトルにする
    ligDir = normalize(ligDir);

    // 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir, // ライトの方向
        pointlight.ptColor, // ライトのカラー
        psIn.normal // サーフェイスの法線
    );
    //減衰なしのリムライトを計算する。
    float3 rimPoint = CalcRimLight(psIn, ligDir, pointlight.ptColor);

    // 距離による影響率を計算する
    // ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - pointlight.ptPosition);

    // 影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / max(pointlight.ptRange * distance, 0.001f);

    // 影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 影響の仕方を指数関数的にする。今回のサンプルでは3乗している
    affect = pow(affect, 3.0f);

    // 拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffPoint *= affect;
  //  specPoint *= affect;
    rimPoint *= affect;

    return diffPoint /*+ rimPoint*/; //specPoint + rimPoint;
}
//スポットライトによる反射光を計算。
float3 CalcLigFromSpotLight(SPSIn psIn)
{
     // このサーフェイスに入射しているポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - spotlight.spPosition;

    // 正規化して大きさ1のベクトルにする
    ligDir = normalize(ligDir);

    // 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir, // ライトの方向
        spotlight.spColor, // ライトのカラー
        psIn.normal // サーフェイスの法線
    );
    //減衰なしのリムライトを計算する。
    float3 rimPoint = CalcRimLight(psIn, spotlight.spDirection, spotlight.spColor);

    // 距離による影響率を計算する
    // ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - spotlight.spPosition);

    // 影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / spotlight.spRange * distance;

    // 影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 影響の仕方を指数関数的にする。今回のサンプルでは3乗している
    affect = pow(affect, 3.0f);

    // 拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffPoint *= affect;
   // specPoint *= affect;
    rimPoint *= affect;
    //入射光と射出方向の角度を求める。
    float angle = dot(ligDir, spotlight.spDirection);
    
    angle = abs(acos(min(angle, 1.0f)));
    
    //角度に比例して小さくなっていく影響率を計算
    affect = 1.0f - 1.0f / spotlight.spAngle * angle;
    //影響率がマイナスにならないように補正。
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    
    //影響の仕方を指数関数的にする。
    affect = pow(affect, 0.5f);
    
    //角度による影響率を反射光に乗算。
    diffPoint *= affect;
  //  specPoint *= affect;
    rimPoint *= affect;
    
    return diffPoint /*+ rimPoint*/; //specPoint+
    
}
//リムライトの計算。
float3 CalcRimLight(SPSIn psIn, float3 direction, float3 color)
{
    //サーフェイスの法線と光の入射方向に依存するリムの強さを求める。
    float power1 = 1.0f - max(0.0f, dot(direction, psIn.normal));
    //サーフェイスの法線と視線の方向に依存するリムの強さを求める。
    float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);
    
    //最終的なリムの強さを求める。
    float limpower = power1 * power2;
    //強さの変化を指数関数的にする。
    limpower = pow(limpower, 1.3f);
    //リムライトのカラーを計算する。
    float3 limcolor = limpower * color;
    
    return limcolor;

}

/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMainCore(SPSIn psIn, uniform bool shadowreceive) : SV_Target0
{
    // ポイントライトによるライティングを計算する
    float3 pointLig = CalcLigFromPointLight(psIn);

    //スポットライトによるライティングを計算する。
    float3 spotLig = CalcLigFromSpotLight(psIn);
   
    
   // アルベドマップ
    float2 uv = psIn.uv;
    uv.x += uvscroll;
    uv.y -= uvscroll;
    
    
 //   float4 color = g_albedo.Sample(g_sampler, uv);
    
    float3 localNormal = g_normalMap.Sample(g_sampler, uv).xyz;

    uv.x -= uvscroll * 0.2f;
    uv.y += uvscroll * 1.8f;
    
    float3 normal = psIn.normal;
    
    //法線マップからタンジェントスペースの法線をサンプリングする
    float3 localNormal2 = g_normalMap.Sample(g_sampler, uv).xyz;
    
    
    //タンジェントスペースの法線を0～1の範囲から-1～1の範囲に復元する
    localNormal = (localNormal - 0.5f) * 2.0f;
    localNormal2 = (localNormal2 - 0.5f) * 2.0f;

    localNormal += localNormal2;
    localNormal = normalize(localNormal);

    //タンジェントスペースの法線をワールドスペースに変換する
    normal = psIn.tangent * localNormal.x + psIn.biNormal * localNormal.y + normal * localNormal.z;
    float3 skyColor = float3(0.6f, 0.850980f, 0.917647f);
    //(153.0f/255.0f, 217.0f/255.0f, 234.0f/255.0f);0.6,0.8509803921568627,0.9176470588235294
    float3 waterColor = float3(0.5f, 0.5f, 0.5f);
    float3 toEye = eyePos - psIn.worldPos;
    toEye = normalize(toEye);
    float t = dot(toEye, normal);
    float3 finalColor = lerp(skyColor, waterColor, t);
    
    float alpha = 1.0f;
    if (t > 0.4f)
    {
        alpha = 0.7f;
    }
    
    // フォグで空となじませる
    t = min(1, length(psIn.worldPos) / 12000.0f);
    float3 fogColor = float3(0.976470f, 0.952941f, 0.894117f);
    //(249.0f / 255.0f, 243.0f / 255.0f, 228.0f / 255.0f);0.9764705882352941,0.9529411764705882,0.8941176470588235
    finalColor = lerp(finalColor, fogColor, pow(t, 0.5f));

    return float4(finalColor, alpha);
}
// モデル用のピクセルシェーダーのエントリーポイント
float4 PSMain(SPSIn psIn) : SV_Target0
{
    return PSMainCore(psIn, false);
}