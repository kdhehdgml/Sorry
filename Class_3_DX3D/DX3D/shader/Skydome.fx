
//--------------------------------------------------------------//
// Skydome
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Skydome_Pass_0_myModel : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\SkyDome.3ds";

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjMatrix : Projection;
float4 gWorldLightPos = float4( -400.00, 400.00, -400.00, 1.00 );
float4 gLightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

texture DiffuseMap_Tex;
sampler2D DiffuseSampler = sampler_state
{
    Texture = (DiffuseMap_Tex);
    MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
    MIPFILTER = LINEAR;
};

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 TexCoord : TEXCOORD0;
    float LightDistance : TEXCOORD1;
};

VS_OUTPUT Skydome_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
	VS_OUTPUT Output;

	Output.Position = mul( Input.Position, gWorldMatrix );
   
	float dist = distance(Output.Position.xyz, gWorldLightPos.xyz);
    Output.LightDistance = dist;
	
	Output.Position = mul( Output.Position, gViewMatrix );
	Output.Position = mul( Output.Position, gProjMatrix );
   
	Output.TexCoord = Input.TexCoord;
	return( Output );
   
}





struct PS_INPUT
{
   float2 TexCoord : TEXCOORD0;
    float LightDistance : TEXCOORD1;
};


float4 Skydome_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{
	float4 albedo = tex2D(DiffuseSampler, Input.TexCoord);
    float4 diffuse = 60.0f / abs(Input.LightDistance - 520) * gLightColor;
    
    return diffuse + albedo;
   
}




//--------------------------------------------------------------//
// Technique Section for Skydome
//--------------------------------------------------------------//
technique Skydome
{
  
   pass Pass_0
   {
		
		VertexShader = compile vs_2_0 Skydome_Pass_0_Vertex_Shader_vs_main();
		PixelShader = compile ps_2_0 Skydome_Pass_0_Pixel_Shader_ps_main();
       
    }

}

