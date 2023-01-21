
cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
    float4 screenParam;
    float2 uvposi;
    int hit;
};



struct SVSIn
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct SPSIn
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

///////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////

Texture2D<float4> g_albedo : register(t0); // アルベドマップ
Texture2D<float4> g_ink : register(t20); //  インク
Texture2D<float4> g_offscreen : register(t21); //  インク
sampler g_sampler : register(s0); // サンプラーステート

/// <summary>
/// インクが落とされる用の頂点シェーダー
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    //座標変換
    SPSIn psIn;
    psIn.pos = mul(mvp, vsIn.pos);
    psIn.uv = vsIn.uv;
    

    return psIn;
}

/// <summary>
/// インクが落とされる用のピクセルシェーダー
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    //求めたUV座標
    float2 inkUV = uvposi;
    float2 ink = float2(0.5f, 0.5f);
    float4 color;
    if (hit == 0)
    {
        //モデルのテクスチャ
        color = g_albedo.Sample(g_sampler, psIn.uv);
    }
    else
    {
        //モデルのテクスチャ
        color = g_offscreen.Sample(g_sampler, psIn.uv);
    }

    //インクのテクスチャ
    float4 inkTextre = g_ink.Sample(g_sampler, ink);
    
    float2 diff = inkUV - psIn.uv;
    float dist = length(diff);
    if (dist < 0.06f)
    {
        //インクを塗る
        color.xyz *= inkTextre;
    }
    float4 test = color;
    return test;
}
