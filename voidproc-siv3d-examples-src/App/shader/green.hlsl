Texture2D       g_texture0 : register(t0);
SamplerState    g_sampler0 : register(s0);

namespace s3d
{
    struct PSInput
    {
        float4 position	: SV_POSITION;
        float4 color	: COLOR0;
        float2 uv		: TEXCOORD0;
    };
}

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_sdfOutlineColor;
    float4 g_sdfShadowColor;
    float4 g_internal;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
   float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

   texColor.g = texColor.r * 0.299 + texColor.g * 0.587 + texColor.b * 0.114;
   texColor.rb = texColor.g * 0.5;

   return (texColor * input.color) + g_colorAdd;
}
