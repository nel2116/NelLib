
struct VS_IN
{ // CPUから渡されてくる頂点データ
    float3 pos : POSITION; // 頂点座標
    float3 normal : NORMAL0; // 法線ベクトル
    float2 uv : TEXCOORD0; // テクスチャ座標
    float4 color : COLOR0; // 頂点カラー
};

struct VS_OUT
{ // 頂点シェーダからピクセルシェーダへ渡すデータ
    float4 pos : SV_POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

cbuffer WVP : register(b0)
{ // ワールド、ビュー、プロジェクション行列
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    // 頂点座標をワールド、ビュー、プロジェクション行列で変換
    output.pos = mul(float4(input.pos, 1.0f), World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);

    // 法線ベクトルをワールド行列で変換
    output.normal = mul(input.normal, (float3x3) World);

    // テクスチャ座標と頂点カラーをそのまま渡す
    output.uv = input.uv;
    output.color = input.color;

    return output;
}