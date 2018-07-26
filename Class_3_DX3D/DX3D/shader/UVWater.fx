
//--------------------------------------------------------------//
// UVAnimation
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
//string UVAnimation_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Torus.3ds";

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjMatrix : Projection;

float4 gWorldLightPosition = float4( 500.00, 500.00, -500.00, 1.00 );
float3 gWorldLightDir = float3( 1, -1, -1 );
float4 gWorldCameraPosition : ViewPosition;
float3 gLightColor = float3(0.70, 0.70, 1.00);

float gTime : Time0_X;
float gBumpiness = float(1.0);
float gUVSpeed = float( 0.25 );


struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;
   float2 mUV: TEXCOORD0;
};

struct VS_OUTPUT 
{
    float4 mPosition : POSITION;
    float2 mUV: TEXCOORD0;
    float3 mDiffuse : TEXCOORD1;
    float3 mViewDir: TEXCOORD2;
    float3 mReflection: TEXCOORD3;
    float3 mNormal : TEXCOORD4;
};

VS_OUTPUT UVAnimation_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
    VS_OUTPUT Output;
   
    Output.mPosition = mul( Input.mPosition, gWorldMatrix );

    float3 lightDir = Output.mPosition.xyz - gWorldLightPosition.xyz;
    lightDir = normalize(lightDir);
   
    float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPosition.xyz);
    Output.mViewDir = viewDir;
   
    Output.mPosition = mul( Output.mPosition, gViewMatrix );
    Output.mPosition = mul(Output.mPosition, gProjMatrix);
   
    float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
    worldNormal = normalize(worldNormal);
    Output.mNormal = worldNormal;
    Output.mDiffuse = dot(-lightDir, worldNormal);
    Output.mReflection = reflect(lightDir, worldNormal);

    Output.mUV = Input.mUV;
   
    return Output;
}


struct PS_INPUT
{
    float2 mUV : TEXCOORD0;
    float3 mDiffuse : TEXCOORD1;
    float3 mViewDir: TEXCOORD2;
    float3 mReflection: TEXCOORD3;
    float3 mNormal : TEXCOORD4;
};

texture DiffuseMap_Tex;
sampler2D DiffuseSampler = sampler_state
{
    Texture = (DiffuseMap_Tex);
    MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
    MIPFILTER = LINEAR;
};
texture NormalMap_Tex;
sampler2D NormalSampler = sampler_state
{
    Texture = (NormalMap_Tex);
    MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
    MIPFILTER = LINEAR;
};



float4 UVAnimation_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
    float2 normalUV = float2(Input.mUV.x + gTime * gUVSpeed, Input.mUV.y);
    float3 normal = tex2D(NormalSampler, normalUV);
    float3 albedo2 = tex2D(DiffuseSampler, Input.mUV + gBumpiness * (normal.xy)).rgb * gLightColor;
    //float3 albedo = tex2D(DiffuseSampler, Input.mUV).rgb;

    //float3 diffuse = saturate(dot(-gWorldLightDir.xyz, normal));
    float3 diffuse = saturate(dot(-gWorldLightDir.xyz, normalize(Input.mNormal)));
    //diffuse += 0.35f;
    float3 reflection = normalize(reflect(gWorldLightDir.xyz, normal));

    //float3 diffuse = saturate(Input.mDiffuse);
    //float3 reflection = normalize(Input.mReflection);
    float3 viewDir = normalize(Input.mViewDir);
    float3 specular = 0;

    if ( diffuse.x > 0 )
    {
        specular = saturate(dot(reflection, -viewDir ));
        specular = pow(specular, 20.0f);
        specular *= gLightColor;
    }

    
    diffuse *= albedo2;
    float3 ambient = float3(0.25f, 0.25f, 0.25f) * albedo2;
   
    //return float4(specular, 1);
    return float4(diffuse + ambient + specular, 0.85f);
}

//--------------------------------------------------------------//
// Technique Section for UVAnimation
//--------------------------------------------------------------//
technique UVAnimation
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 UVAnimation_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 UVAnimation_Pass_0_Pixel_Shader_ps_main();
   }

}

