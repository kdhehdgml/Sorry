

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

float4 gWorldLightPos = float4(500.00, 500.00, -500.00, 1.00);
float4 gWorldCameraPos : ViewPosition;
float gPower = float(20.0f);

texture ShadowMap_Tex;
sampler2D ShadowSampler = sampler_state
{
    Texture = (ShadowMap_Tex);
    /*
	MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
    MIPFILTER = LINEAR;
	*/
};

texture DiffuseMap_Tex;
sampler2D DiffuseSampler = sampler_state
{
	Texture = (DiffuseMap_Tex);
	/*
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
	MIPFILTER = LINEAR;
	*/
};

struct VS_INPUT 
{
	float4 Position : POSITION0;
	float3 Normal : NORMAL;
	float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT 
{
	float4 Position : POSITION0;
    float2 mTexCoord : TEXCOORD0;
	float4 ClipPosition : TEXCOORD1;
	float Diffuse : TEXCOORD2;
    float3 mViewDir : TEXCOORD3;
    float3 mReflection : TEXCOORD4;
   
};

VS_OUTPUT ApplyShadow_VS_main( VS_INPUT Input )
{
	VS_OUTPUT Output;
   
	float4 worldPos = mul( Input.Position, gWorldMatrix);
	Output.Position = mul( worldPos, gViewMatrix);
	Output.Position = mul( Output.Position, gProjMatrix);
   
	Output.ClipPosition = mul( worldPos, gLightViewMatrix);
	Output.ClipPosition = mul( Output.ClipPosition, gLightProjMatrix);
   
    float3 viewDir = normalize(worldPos.xyz - gWorldCameraPos.xyz);
	Output.mViewDir = viewDir;

	float3 lightDir = normalize(worldPos.xyz - gWorldLightPos.xyz);
	float3 worldNormal = normalize(mul ( Input.Normal, (float3x3)gWorldMatrix));
	Output.Diffuse = dot(-lightDir, worldNormal);
    Output.mReflection = reflect(lightDir, worldNormal);

    Output.mTexCoord = Input.mTexCoord;
	return( Output );
   
}




struct PS_INPUT 
{
    float2 TexCoord : TEXCOORD0;
	float4 ClipPosition : TEXCOORD1;
	float  Diffuse : TEXCOORD2;
    float3 mViewDir : TEXCOORD3;
    float3 mReflection : TEXCOORD4;
};


float4 ApplyShadow_PS_main(PS_INPUT Input) : COLOR0
{   
    float3 diffuse = saturate(Input.Diffuse);
    float3 reflection = normalize(Input.mReflection);
    float3 viewDir = normalize(Input.mViewDir);
    float3 specular = 0;
   
    float4 albedo = tex2D(DiffuseSampler, Input.TexCoord);
   
    if (diffuse.r > 0)
    {
        specular = saturate(dot(reflection, -viewDir));
        specular = pow(specular, gPower);
        //specular = specular * albedo.rgb * 4;
    }
    diffuse = diffuse * albedo.rgb;
    float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo.rgb;
	
	float currentDepth = Input.ClipPosition.z / Input.ClipPosition.w;
   
	float2 uv = Input.ClipPosition.xy / Input.ClipPosition.w;
	uv.y = -uv.y;
	uv = uv * 0.5 + 0.5;
   
	float shadowDepth = tex2D(ShadowSampler, uv).r;
   
	if ( currentDepth > shadowDepth + 0.0000125f)
	{
		diffuse *= 0.5f;
	}
   
    return float4(diffuse + ambient + specular, 1);
   
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

