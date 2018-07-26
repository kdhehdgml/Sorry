

//--------------------------------------------------------------//
// ShadowMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// ApplyShadow
//--------------------------------------------------------------//
string ShadowMapping_ApplyShadow_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Torus.3ds";

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjMatrix : Projection;
float4x4 gLightViewMatrix;
float4x4 gLightProjMatrix : Projection;

float4 gObjectColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

texture ShadowMap_Tex;
sampler2D ShadowSampler = sampler_state
{
    Texture = (ShadowMap_Tex);
};

struct VS_INPUT 
{
	float4 Position : POSITION0;
};

struct VS_OUTPUT 
{
	float4 Position : POSITION0;
    float4 ClipPosition : TEXCOORD1;
};

VS_OUTPUT ApplyShadow_VS_main( VS_INPUT Input )
{
	VS_OUTPUT Output;
   
	float4 worldPos = mul( Input.Position, gWorldMatrix);
	Output.Position = mul( worldPos, gViewMatrix);
	Output.Position = mul( Output.Position, gProjMatrix);
   
	Output.ClipPosition = mul( worldPos, gLightViewMatrix);
	Output.ClipPosition = mul( Output.ClipPosition, gLightProjMatrix);
   
	return( Output );
   
}




struct PS_INPUT 
{
	float4 ClipPosition : TEXCOORD1;
};


float4 ApplyShadow_PS_main(PS_INPUT Input) : COLOR0
{   
    float4 color = gObjectColor;
	float currentDepth = Input.ClipPosition.z / Input.ClipPosition.w;
   
	float2 uv = Input.ClipPosition.xy / Input.ClipPosition.w;
	uv.y = -uv.y;
	uv = uv * 0.5 + 0.5;
   
	float shadowDepth = tex2D(ShadowSampler, uv).r;
   
	if ( currentDepth > shadowDepth + 0.0000125f)
	{
        color *= 0.5f;
    }
   
    return float4(color);
   
}




//--------------------------------------------------------------//
// Technique Section for ShadowMapping
//--------------------------------------------------------------//
technique ShadowMapping
{
   pass ApplyShadow
   {
        VertexShader = compile vs_2_0 ApplyShadow_VS_main();
      PixelShader = compile ps_2_0 ApplyShadow_PS_main();
   }

}

