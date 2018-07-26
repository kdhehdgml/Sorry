
//--------------------------------------------------------------//
// ColorShader
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string ColorShader_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjMatrix;

float gConst;
float3 gColor = float3(0, 0, 1);

struct VS_INPUT 
{
    float4 mPosition : POSITION;
    float4 mColor : COLOR0;
    //float3 mNormal : NORMAL;
};

struct VS_OUTPUT 
{
    float4 mPosition : POSITION;
    float4 mColor : COLOR0;
};

VS_OUTPUT VS( VS_INPUT Input )
{
    VS_OUTPUT Output;
    //Output.mPosition = Input.mPosition + float4(Input.mNormal * gConst, 0);
    Output.mPosition = Input.mPosition;
    Output.mPosition = mul(Output.mPosition, gWorldMatrix);
    Output.mPosition = mul(Output.mPosition, gViewMatrix);
    Output.mPosition = mul(Output.mPosition, gProjMatrix);
    Output.mColor = Input.mColor;

   return Output;
}

struct PS_INPUT
{
    float4 mPosition : POSITION;
    float4 mColor : COLOR0;
};

float4 PS(PS_INPUT Input) : COLOR
{   
    //return (float4(1, 0, 0, 0));
    return (Input.mColor);
}

//--------------------------------------------------------------//
// Technique Section for ColorShader
//--------------------------------------------------------------//
technique ColorShader
{
   pass Pass_0
   {
        VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

