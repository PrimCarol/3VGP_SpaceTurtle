#version 330
out float FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gMetalRough;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDepth;
//uniform sampler2D ssaoNoise;

uniform vec3 samples[64];
uniform mat4 projMatrix;
const vec2 noiseScale = vec2(1600.0/4.0, 900.0/4.0);

float radius = 10.0;
float kernelSize = 2.0;

void main(){ 

	vec3 fragPos   = texture(gPosition, TexCoords).xyz;
	vec3 normal    = texture(gNormal, TexCoords).rgb;
	//vec3 randomVec = texture(ssaoNoise, TexCoords * noiseScale).xyz;  
	vec3 randomVec = vec3(0.5,0.5,0.5);  

	vec3 tangent   = normalize(randomVec - normal * dot(randomVec, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 TBN       = mat3(tangent, bitangent, normal);  

	float bias = 0.05;

	float occlusion = 0.0;
	for(int i = 0; i < kernelSize; ++i){
		vec3 samplePos = TBN * samples[i];
		samplePos = fragPos + samplePos * radius; 
		
		vec4 offset = vec4(samplePos, 1.0);	
		offset      = projMatrix * offset;
		offset.xyz /= offset.w;
		offset.xyz  = offset.xyz * 0.5 + 0.5;

		float sampleDepth = texture(gPosition, offset.xy).z;

		occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0);
	}

	//FragColor = occlusion;
	FragColor = occlusion;
}