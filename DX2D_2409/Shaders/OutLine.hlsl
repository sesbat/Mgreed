struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Normal : NORMAL;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = mul(input.Pos, WorldViewProjectionMatrix);
    output.Normal = input.Normal;
    return output;
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Normal : NORMAL;
};

float4 PS(PS_INPUT input) : SV_Target
{
    return float4(input.Normal, 1.0);
}

Texture2D depthMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState sampleType : register(s0);

float depthDifference(float2 uv)
{
    float centerDepth = depthMap.Sample(sampleType, uv).r;
    float depthNorth = depthMap.Sample(sampleType, uv + float2(0.0, -1.0) * pixelSize).r;
    float depthSouth = depthMap.Sample(sampleType, uv + float2(0.0, 1.0) * pixelSize).r;
    float depthEast = depthMap.Sample(sampleType, uv + float2(1.0, 0.0) * pixelSize).r;
    float depthWest = depthMap.Sample(sampleType, uv + float2(-1.0, 0.0) * pixelSize).r;

    float maxDepth = max(max(max(depthNorth, depthSouth), depthEast), depthWest);
    float minDepth = min(min(min(depthNorth, depthSouth), depthEast), depthWest);

    return maxDepth - minDepth;
}

float normalDifference(float2 uv)
{
    float3 centerNormal = normalMap.Sample(sampleType, uv).rgb;
    float3 normalNorth = normalMap.Sample(sampleType, uv + float2(0.0, -1.0) * pixelSize).rgb;
    float3 normalSouth = normalMap.Sample(sampleType, uv + float2(0.0, 1.0) * pixelSize).rgb;
    float3 normalEast = normalMap.Sample(sampleType, uv + float2(1.0, 0.0) * pixelSize).rgb;
    float3 normalWest = normalMap.Sample(sampleType, uv + float2(-1.0, 0.0) * pixelSize).rgb;

    float maxDiff = max(max(distance(centerNormal, normalNorth), distance(centerNormal, normalSouth)),
                        max(distance(centerNormal, normalEast), distance(centerNormal, normalWest)));
    
    return maxDiff;
}

float4 PS_Post(PS_INPUT input) : SV_Target
{
    float2 uv = input.TexCoords;
    float depthDiff = depthDifference(uv);
    float normDiff = normalDifference(uv);

    bool isEdge = depthDiff > depthThreshold || normDiff > normalThreshold;
    
    return isEdge ? float4(1, 0, 0, 1) : float4(0, 0, 0, 0);
}