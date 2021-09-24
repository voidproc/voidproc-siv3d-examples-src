Texture2D    g_texture0 : register(t0);
SamplerState g_sampler0 : register(s0);

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

cbuffer WhiteEffectConstants : register(b1)
{
	float strength;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	float4 srcColor = g_texture0.Sample(g_sampler0, input.uv);

	srcColor.rgb += (float3(1.0, 1.0, 1.0) - srcColor.rgb) * strength;

	return (srcColor * input.color) + g_colorAdd;
}