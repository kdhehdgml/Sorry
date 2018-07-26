

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
float   gMtl_P = float(20.0f);

struct VS_INPUT 
{
    float4 Position : POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
};

struct VS_OUTPUT 
{
    float4 Position : POSITION;
    float4 Color : COLOR;
    float3 Diffuse : TEXCOORD1;
    float3 ViewDir : TEXCOORD2;
    float3 Reflection : TEXCOORD3;
};

VS_OUTPUT Lighting_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
    VS_OUTPUT Output;
    Output.Position = mul(Input.Position, gWorldMatrix);
   
    float3 lightDir = Output.Position.xyz - gWorldLightPos.xyz;
    lightDir = normalize(lightDir);
   
    float3 viewDir = normalize(Output.Position.xyz - gWorldCameraPos.xyz);
    Output.ViewDir = viewDir;
   
    Output.Position = mul(Output.Position, gViewMatrix);
    Output.Position = mul(Output.Position, gProjMatrix);
   
   
    float3 worldNormal = mul(Input.Normal, (float3x3)gWorldMatrix);
    worldNormal = normalize(worldNormal);
   
    Output.Diffuse = dot(-lightDir, worldNormal);
    Output.Reflection = reflect(lightDir, worldNormal);
   
    Output.Color = Input.Color;

    return Output;
}

struct PS_INPUT
{
    float4 Color : COLOR;
    float3 Diffuse : TEXCOORD1;
    float3 ViewDir : TEXCOORD2;
    float3 Reflection : TEXCOORD3;
};

float4 Lighting_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{   
    float3 diffuse = saturate(Input.Diffuse);
    float3 reflection = normalize(Input.Reflection);
    float3 viewDir = normalize(Input.ViewDir);
    float3 specular = 0;
   
    if ( diffuse.x > 0 )
    {
        specular = saturate(dot(reflection, -viewDir));
        specular = pow(specular, gMtl_P);
    }

    float4 albedo = Input.Color;
    diffuse = diffuse * albedo.rgb;
   
    float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo.rgb;
   
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

