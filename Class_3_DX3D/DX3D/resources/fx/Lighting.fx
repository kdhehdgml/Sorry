
//--------------------------------------------------------------//
// Lighting
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Lighting_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.x";

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjMatrix : Projection;
float4   gWorldLightPos = float4( -500.00, 500.00, -500.00, 1.00 );
float4   gWorldCameraPos : ViewPosition;

float4 gMtl_D = float4(1.0, 1.0, 1.0, 1.0);
float4 gMtl_A = float4(1.0, 1.0, 1.0, 1.0);
float4 gMtl_S = float4(1.0, 1.0, 1.0, 1.0);
float gMtl_P = float(20.0f);


texture DiffuseMap_Tex;

sampler2D DiffuseSampler = sampler_state
{
	Texture = (DiffuseMap_Tex);
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
	MIPFILTER = LINEAR;
	ADDRESSU = WRAP;
	ADDRESSV = WRAP;
};

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal : NORMAL;
    float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
    float2 mTexCoord : TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir : TEXCOORD2;
   float3 mReflection : TEXCOORD3;
};

VS_OUTPUT Lighting_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
	VS_OUTPUT Output;
	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
   
	float3 lightDir = Output.mPosition.xyz - gWorldLightPos.xyz;
	lightDir = normalize(lightDir);
   
	float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPos.xyz);
	Output.mViewDir = viewDir;
   
	Output.mPosition = mul(Output.mPosition, gViewMatrix);
	Output.mPosition = mul(Output.mPosition, gProjMatrix);
   
   
	float3 worldNormal = mul(Input.mNormal, (float3x3)gWorldMatrix);
	worldNormal = normalize(worldNormal);
   
	Output.mDiffuse = dot(-lightDir, worldNormal);
	Output.mReflection = reflect(lightDir, worldNormal);
   
	Output.mTexCoord = Input.mTexCoord;

	return Output;
}



struct PS_INPUT
{
	float2 mTexCoord : TEXCOORD0;
	float3 mDiffuse : TEXCOORD1;
	float3 mViewDir : TEXCOORD2;
	float3 mReflection : TEXCOORD3;
};


float4 Lighting_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{   
	float3 diffuse = saturate(Input.mDiffuse);
	float3 reflection = normalize(Input.mReflection);
	float3 viewDir = normalize(Input.mViewDir);
	float3 specular = 0;
   
	float4 albedo = tex2D(DiffuseSampler, Input.mTexCoord);
	
	if ( diffuse.x > 0 )
	{
		specular = saturate(dot(reflection, -viewDir));
        specular = pow(specular, gMtl_P);
        specular = specular * gMtl_S.rgb;
    }
    diffuse = diffuse * albedo.rgb * gMtl_D.rgb;
    
	float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo.rgb * gMtl_A.rgb;
   
	return float4( diffuse + ambient + specular, 1);
}

//--------------------------------------------------------------//
// Technique Section for Lighting
//--------------------------------------------------------------//
technique Lighting
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Lighting_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Lighting_Pass_0_Pixel_Shader_ps_main();
   }

}

