
cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
    float4 screenParam;
    float2 uvposi;
    int hit;
    int player;
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

    float2 syoutotu = inkUV;
    
    syoutotu.x *= 1600.0f;
    syoutotu.y *= 900.0f;
    
    float2 LeftUP = syoutotu;
    LeftUP.x -= 120.0f;
    LeftUP.y -= 67.5f;
    
    float2 RightDown = syoutotu;
    RightDown.x += 120.0f;
    RightDown.y += 67.5f;
    
    float2 pixelposi = psIn.uv;
    pixelposi.x *= 1600.0f;
    pixelposi.y *= 900.0f;
    
    if (pixelposi.x > LeftUP.x && pixelposi.x < RightDown.x &&
        pixelposi.y > LeftUP.y && pixelposi.y < RightDown.y)
    {
        ink.x = pixelposi.x - LeftUP.x;
        ink.y = pixelposi.y - LeftUP.y;
        ink.x /= 240.0f;
        ink.y /= 135.0f;
        //インクのテクスチャ
        float3 paint = g_ink.Sample(g_sampler, ink);
        color.xyz *= paint;
        if (paint.x < 1.0f && paint.y < 1.0f)
        {
            if (player == 1)
            {
                color.x = paint.z;
                color.y = 0.0f;
                color.z = 0.0f;
            }

            if (player == 0)
            {
                color.x = 0.0f;
                color.y = 0.0f;
                color.z = 0.8f;
            }
        }
    }
    float4 test = color;
    return test;
}
