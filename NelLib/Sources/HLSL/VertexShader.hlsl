struct VS_INPUT
{
    float4 pos : POSITION;
};

float4 main(VS_INPUT vin) : SV_POSITION
{
	return vin.pos;
}