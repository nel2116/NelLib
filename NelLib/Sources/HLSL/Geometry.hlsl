struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

// �e�N�X�`���T���v���[
Texture2D tex : register(t0);
SamplerState sp : register(s0);

float4 main(PS_IN pin) : SV_TARGET0
{
    float4 color = pin.color;
    // �e�N�X�`��������ꍇ
    color *= tex.Sample(sp, pin.uv);
    
    return color;
}