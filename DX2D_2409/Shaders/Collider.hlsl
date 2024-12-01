//Sementic : �Ű������� ��ȯ �ڷ����� ��� �뵵
//SV(System Value)

cbuffer VPBuffer : register(b0)
{
	//matrix == flaot4x4	
	float4x4 view;
	matrix projection;
}

cbuffer WorldBuffer : register(b1)
{
	matrix world;
}

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

struct VertexInput
{
	float4 pos : POSITION;	
};

struct PixelInput
{
	float4 pos : SV_POSITION;	
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);	
		
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}