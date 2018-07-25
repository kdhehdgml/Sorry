
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
float4 gWorldCameraPosition : ViewPosition;
float3 gLightColor = float3(0.70, 0.70, 1.00);

float gTime : Time0_X;
float gWaveHeight = float( 3.00 );
float gSpeed = float( 2.00 );
float gWaveFrequency = float( 10.00 );
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
};

VS_OUTPUT UVAnimation_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   
   float cosTime = gWaveHeight * cos(gTime * gSpeed + Input.mUV.x*gWaveFrequency);
   Input.mPosition.y += cosTime;

   Output.mPosition = mul( Input.mPosition, gWorldMatrix );

   float3 lightDir = Output.mPosition.xyz - gWorldLightPosition.xyz;
   lightDir = normalize(lightDir);
   
   float3 viewDir = normalize(Output.mPosition.xyz - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;
   
   Output.mPosition = mul( Output.mPosition, gViewMatrix );
    Output.mPosition = mul(Output.mPosition, gProjMatrix);
   
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   worldNormal = normalize(worldNormal);

   Output.mDiffuse = dot(-lightDir, worldNormal);
   Output.mReflection = reflect(lightDir, worldNormal);

   Output.mUV = Input.mUV + float2(gTime * gUVSpeed, 0);
   
   return Output;
}


struct PS_INPUT
{
   float2 mUV : TEXCOORD0;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 mReflection: TEXCOORD3;
};

texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Fieldstone.tga";
>;
sampler2D DiffuseSampler = sampler_state
{
	 Texture = (DiffuseMap_Tex);
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};
texture SpecularMap_Tex
<
   string ResourceName = "..\\05_DiffuseSpecularMapping\\fieldstone_SM.tga";
>;
sampler2D SpecularSampler = sampler_state
{
   Texture = (SpecularMap_Tex);
};



float4 UVAnimation_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
    float3 diffuse = saturate(Input.mDiffuse);
    float3 reflection = normalize(Input.mReflection);
    float3 viewDir = normalize(Input.mViewDir); 
    float3 specular = 0;

    if ( diffuse.x > 0 )
    {
        specular = saturate(dot(reflection, -viewDir ));
        specular = pow(specular, 20.0f);
      
        float4 specularIntensity  = tex2D(SpecularSampler, Input.mUV);
        specular *= specularIntensity.rgb * gLightColor;
    }

    float3 albedo = tex2D(DiffuseSampler, Input.mUV).rgb;
    diffuse = gLightColor * albedo.rgb * saturate(Input.mDiffuse);
    float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo;
   
    return float4(ambient + diffuse + specular, 1);
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

