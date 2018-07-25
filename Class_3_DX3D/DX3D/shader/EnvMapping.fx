

//--------------------------------------------------------------//
// EnvMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string EnvMapping_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Teapot.3ds";

float4x4 gWorldMatrix : World;
float4x4 gWVPMatrix : WorldViewProjection;

float4   gWorldLightPosition = float4( 500.00, 500.00, -500.00, 1.00 );
float4   gWorldCameraPosition : ViewPosition;

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal : NORMAL;
   float3 mBinormal : BINORMAL;
   float3 mTangent : TANGENT;
   float2 mUV: TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
   float2 mUV: TEXCOORD0;
   float3 mLightDir : TEXCOORD1;
   float3 mViewDir : TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
};

VS_OUTPUT EnvMapping_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   Output.mPosition = mul(Input.mPosition, gWVPMatrix);
   Output.mUV = Input.mUV;
   
   float4 worldPos = mul(Input.mPosition, gWorldMatrix);
   
   float3 lightDir = worldPos.xyz - gWorldLightPosition.xyz;
   Output.mLightDir = normalize(lightDir);
   
   float3 viewDir = normalize(worldPos.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;
   
   float3 worldTangent = mul(Input.mTangent, (float3x3)gWorldMatrix);
   Output.T = normalize(worldTangent);
   
   float3 worldBinormal = mul(Input.mBinormal, (float3x3)gWorldMatrix);
   Output.B = normalize(worldBinormal);
   
   float3 worldNormal = mul(Input.mNormal, (float3x3)gWorldMatrix);
   Output.N = normalize(worldNormal);
   
   return Output;
}

struct PS_INPUT
{
   float2 mUV : TEXCOORD0;
   float3 mLightDir : TEXCOORD1;
   float3 mViewDir : TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
};

texture DiffuseMap_Tex;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
   MINFILTER = LINEAR;
   MAGFILTER = LINEAR;
};
texture SpecularMap_Tex;
sampler2D SpecularSampler = sampler_state
{
   Texture = (SpecularMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture NormalMap_Tex;
sampler2D NormalSampler = sampler_state
{
   Texture = (NormalMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture EnvMap_Tex;
samplerCUBE EnvSampler = sampler_state
{
   Texture = (EnvMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};

float3 gLightColor = float3( 0.70, 0.70, 1.00 );


float4 EnvMapping_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{   
   float3 tangentNormal = tex2D(NormalSampler, Input.mUV).xyz;
   tangentNormal.z += 6.0f;
   tangentNormal = normalize(tangentNormal * 2 - 1);
   tangentNormal = float3(0, 0, 1);
   
   float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   //TBN = transpose(TBN);
   
   //float3 worldNormal = mul(TBN, tangentNormal);
    float3 worldNormal = mul(tangentNormal, TBN);
   
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   float3 lightDir = normalize(Input.mLightDir);
   
   float3 diffuse = saturate(dot(worldNormal, -lightDir));
   diffuse = gLightColor * albedo.rgb * diffuse;
   
   float3 specular = 0;
   float3 viewDir = normalize(Input.mViewDir);
   
   if ( diffuse.x > 0 )
   {
      float3 reflection = reflect(lightDir, worldNormal);
      
      specular = saturate(dot(reflection, -viewDir));
      specular = pow(specular, 20.0f);
      
      float4 specularIntensity = tex2D(SpecularSampler, Input.mUV);
      specular *= specularIntensity.rgb * gLightColor;
   }
   
   float3 viewReflect = reflect(viewDir, worldNormal);
   float3 env = texCUBE(EnvSampler, viewReflect).rgb;
   
   float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo.rgb;

    return float4(env, 1);
    //return float4(env +  ambient + diffuse + specular, 1);
   
}

//--------------------------------------------------------------//
// Technique Section for EnvMapping
//--------------------------------------------------------------//
technique EnvMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 EnvMapping_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 EnvMapping_Pass_0_Pixel_Shader_ps_main();
   }

}

