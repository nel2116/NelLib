struct PS_INPUT
{
    float4 pos : POSITION;
};

float4 main(PS_INPUT pin) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}