#version 330
out vec3 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gMetalRough;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDepth;
uniform sampler2D ssaoNoise;

uniform vec3 samples[64];
uniform mat4 projMatrix;
uniform mat4 viewMatrix;
const vec2 noiseScale = vec2(1600.0/4.0, 900.0/4.0);

float radius = 0.5;
float bias = 0.08;
float kernelSize = 64.0;

void main(){ 
    vec4 wordlPos   = texture(gPosition, TexCoords);

    vec3 fragPos   = (viewMatrix * vec4(wordlPos.xyz, 1.0)).xyz;
    vec3 normal    = (viewMatrix * vec4((texture(gNormal, TexCoords).xyz * 2.0 - 1.0), 0.0)).xyz;
    vec3 randomVec = texture(ssaoNoise, TexCoords * noiseScale).xyz;  
    
    vec3 tangent   = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 binormal  = cross(normal, tangent);
    mat3 TBN       = mat3(tangent, binormal, normal);
    
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; i++){
        vec3 thissample = fragPos + TBN * samples[i] * radius;
        vec4 screenSample = projMatrix * vec4(thissample, 1.0);
        screenSample.xyz /= screenSample.w;
        screenSample.xyz = screenSample.xyz * 0.5 + 0.5;

        //vec4 fragPosViewSpace = viewMatrix * vec4(FragPos, 1.0);
        //float depthValue = abs((fragPosViewSpace.z + 1.0) * 2.0);

        vec3 sampleWorldPos = texture(gPosition, screenSample.xy).xyz;
        float sampleDepth = (viewMatrix * vec4(sampleWorldPos, 1.0)).z;
        float rangeCheck = smoothstep(0.0,1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= thissample.z + bias ? 1.0 : 0.0) * rangeCheck;

    }

    float result = pow(1.0 - occlusion / kernelSize, 2);
    //float result = 1.0 - occlusion / kernelSize;
    FragColor = vec3(result,result,result);
}