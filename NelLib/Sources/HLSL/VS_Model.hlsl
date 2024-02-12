
struct VS_IN
{ // CPU����n����Ă��钸�_�f�[�^
    float3 pos : POSITION; // ���_���W
    float3 normal : NORMAL0; // �@���x�N�g��
    float2 uv : TEXCOORD0; // �e�N�X�`�����W
    float4 color : COLOR0; // ���_�J���[
};

struct VS_OUT
{ // ���_�V�F�[�_����s�N�Z���V�F�[�_�֓n���f�[�^
    float4 pos : SV_POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

cbuffer WVP : register(b0)
{ // ���[���h�A�r���[�A�v���W�F�N�V�����s��
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    // ���_���W�����[���h�A�r���[�A�v���W�F�N�V�����s��ŕϊ�
    output.pos = mul(float4(input.pos, 1.0f), World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);

    // �@���x�N�g�������[���h�s��ŕϊ�
    output.normal = mul(input.normal, (float3x3) World);

    // �e�N�X�`�����W�ƒ��_�J���[�����̂܂ܓn��
    output.uv = input.uv;
    output.color = input.color;

    return output;
}