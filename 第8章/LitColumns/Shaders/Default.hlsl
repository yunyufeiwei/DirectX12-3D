// Ĭ����ɫ����Ŀǰ��֧�ֹ���

// ��Դ������Ĭ��ֵ
#ifndef NUM_DIR_LIGHTS
    #define NUM_DIR_LIGHTS 3
#endif

#ifndef NUM_POINT_LIGHTS
    #define NUM_POINT_LIGHTS 0
#endif

#ifndef NUM_SPOT_LIGHTS
    #define NUM_SPOT_LIGHTS 0
#endif

// �����˹������õĽṹ���뺯��
#include "LightingUtil.hlsl"

// ÿ֡�������仯�ĳ�������

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
};

cbuffer cbMaterial : register(b1)
{
	float4 gDiffuseAlbedo;
    float3 gFresnelR0;
    float  gRoughness;
	float4x4 gMatTransform;
};

// ���ƹ��������õ����������
cbuffer cbPass : register(b2)
{
    float4x4 gView;
    float4x4 gInvView;
    float4x4 gProj;
    float4x4 gInvProj;
    float4x4 gViewProj;
    float4x4 gInvViewProj;
    float3 gEyePosW;
    float cbPerObjectPad1;
    float2 gRenderTargetSize;
    float2 gInvRenderTargetSize;
    float gNearZ;
    float gFarZ;
    float gTotalTime;
    float gDeltaTime;
    float4 gAmbientLight;

    // ����ÿ����MaxLightsΪ��Դ�������ֵ�Ķ�����˵������[0, NUM_DIR_LIGHTS)��ʾ���Ƿ����Դ
    // ����[NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS)��ʾ���ǵ��Դ
    // ����[NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)��ʾ���Ǿ۹�ƹ�Դ
    Light gLights[MaxLights];
};
 
struct VertexIn
{
	float3 PosL    : POSITION;
    float3 NormalL : NORMAL;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout = (VertexOut)0.0f;
	
    // ������任������ռ�
    float4 posW = mul(float4(vin.PosL, 1.0f), gWorld);
    vout.PosW = posW.xyz;

    // ����������е��ǵȱ����ţ�����������Ҫʹ������������ת�þ���
    vout.NormalW = mul(vin.NormalL, (float3x3)gWorld);

    // ������任����βü��ռ�
    vout.PosH = mul(posW, gViewProj);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    // �Է��߲�ֵ���ܵ�����ǹ淶���������Ҫ�ٴζ������й淶������
    pin.NormalW = normalize(pin.NormalW);

    // ���߾�������һ�㷴�䵽�۲����һ�����ϵ�����
    float3 toEyeW = normalize(gEyePosW - pin.PosW);

	// ��ӹ���
    float4 ambient = gAmbientLight*gDiffuseAlbedo;

    // ֱ�ӹ���
    const float shininess = 1.0f - gRoughness;
    Material mat = { gDiffuseAlbedo, gFresnelR0, shininess };
    float3 shadowFactor = 1.0f;
    float4 directLight = ComputeLighting(gLights, mat, pin.PosW, pin.NormalW, toEyeW, shadowFactor);

    float4 litColor = ambient + directLight;

    // ������������л�ȡapphaֵ�ĳ����ֶ�
    litColor.a = gDiffuseAlbedo.a;

    return litColor;
}


