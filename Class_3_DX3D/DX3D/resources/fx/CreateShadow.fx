

//--------------------------------------------------------------//
// ShadowMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// CreateShadow
//--------------------------------------------------------------//
string ShadowMapping_CreateShadow_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Torus.3ds";

float4x4 gWorldMatrix : World;
float4x4 gLightViewMatrix;
float4x4 gLightProjMatrix : Projection;

float4 gWorldLightPos;

struct VS_INPUT 
{
	float4 Position : POSITION0;
};

struct VS_OUTPUT 
{
	float4 Position : POSITION0;
	float4 ClipPosition : TEXCOORD1;
   
};

VS_OUTPUT CreateShadow_VS_main(VS_INPUT Input)
{
	VS_OUTPUT Output;
    
	Output.Position = mul( Input.Position, gWorldMatrix );
	Output.Position = mul( Output.Position, gLightViewMatrix);
	Output.Position = mul( Output.Position, gLightProjMatrix);
   
	Output.ClipPosition = Output.Position;
   
	return( Output );
   
}


struct PS_INPUT 
{
	float4 ClipPosition : TEXCOORD1;
   
};

float4 CreateShadow_PS_main(PS_INPUT Input) : COLOR0
{   
	float depth = Input.ClipPosition.z / Input.ClipPosition.w;
	return( float4( depth.xxx, 1.0f ) );
   
}




//--------------------------------------------------------------//
// Technique Section for ShadowMapping
//--------------------------------------------------------------//
technique ShadowMapping
{
   pass CreateShadow
   <
      string Script = "RenderColorTarget0 = ShadowMap_Tex;"
                      "ClearColor = (255, 255, 255, 255);"
                      "ClearDepth = 1.000000;";
   >
   {
      VertexShader = compile vs_2_0 CreateShadow_VS_main();
      PixelShader = compile ps_2_0 CreateShadow_PS_main();
   }

}

