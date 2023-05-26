#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gMetalRough;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDepth;
uniform sampler2D ssaoNoise;
uniform samplerCube gSkybox;

// Necesario
uniform vec3 viewPos;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

// Extra
uniform int visualMode;

// Light Dir
struct DirLight{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight u_DirectLight;

// Pointlight
struct PointLight{
	vec3 position;

	float linear;
	float quadratic;
    float radius;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform float far_plane;
uniform PointLight u_PointLight;

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};
uniform SpotLight u_SpotLight;

// 0 -> None
// 1 -> Directional
// 2 -> Point
// 3 -> Spot
uniform int u_lightType; 

// Shadows
uniform mat4 lightSpaceMatrix[3];
uniform sampler2D shadowMap[3];
uniform float cascadeEndShadow[3];

// Cabeceras
vec3 CalcLight(PointLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 F0);
vec3 CalcLight(DirLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 F0);
vec3 CalcLight(SpotLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 F0);

float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal, vec3 objPosition, sampler2D shadowMap);
float CalcShadow(vec3 lightPos, vec3 objPosition, samplerCube shadowMap);

// --- PBR ----
const float PI = 3.14159265359;
float distributionGGX(vec3 normal, vec3 halfDir, float roughness);
float geometrySchlickGGX(float dotNV, float roughness);
float geometrySmith(vec3 normal, vec3 viewDir, vec3 lightDir, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);

// ---- SSAO -----
vec3 calcularSSAO();
uniform int kernelSize;
uniform float radius;
uniform float bias;
uniform int intensitySSO;
uniform vec3 samples[64];

vec3 Diffuse;
float Specular;
float Metallic;
float Roughness;
vec3 FragPos;
vec3 Normal;
float Depth;

void main(){ 

    // ---- G-Buffer Data ----
    //Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    Diffuse = pow(texture(gAlbedoSpec, TexCoords).rgb, vec3(2.2));
    Specular = texture(gAlbedoSpec, TexCoords).a;
    Metallic = texture(gMetalRough, TexCoords).r;
    Roughness = texture(gMetalRough, TexCoords).g;
    FragPos = texture(gPosition, TexCoords).rgb;
    Normal = texture(gNormal, TexCoords).rgb;
    Depth = texture(gDepth, TexCoords).r;

    if(Normal == vec3(0.0)){discard;}
    
    float shadow = 1.0;

    // -----------------
    vec3 normals = normalize(Normal * 2.0 - 1.0);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Aqui iria el skybox? en el primer MIX
    vec3 reflectDir = reflect(viewDir, normals);
    vec3 skyboxColor = texture(gSkybox, -reflectDir).rgb;
    
    vec3 F0 = vec3(0.04);
    //vec3 F0 = skyboxColor;
    F0 = mix(F0, Diffuse, Metallic);

    vec3 outRadiance = vec3(0.0);

    //vec3 ambientOcclusion = calcularSSAO();
    //Diffuse *= ambientOcclusion;

    if(visualMode == 0){
        if(u_lightType == 1){ // DirLight
            outRadiance = CalcLight(u_DirectLight, viewDir, normals, FragPos, Diffuse, Roughness, Metallic, F0);
        

            // select cascade layer
            vec4 fragPosViewSpace = viewMatrix * vec4(FragPos, 1.0);
            float depthValue = abs((fragPosViewSpace.z + 1.0) * 2.0);
    
            int layer = -1;
            for (int i = 0; i < 3; ++i){
                if (depthValue < cascadeEndShadow[i]){
                    layer = i;
                    break;
                }
            }
            if (layer == -1){
                layer = 2;
            }
    
            vec4 fragPosLightSpace = lightSpaceMatrix[layer] * vec4(FragPos, 1.0);
            shadow = CalcShadow(fragPosLightSpace, u_DirectLight.direction, Normal, FragPos, shadowMap[layer]);

            //vec4 fragPosLightSpace = lightSpaceMatrix[1] * vec4(FragPos, 1.0);
            //shadow = CalcShadow(fragPosLightSpace, u_DirectLight.direction, Normal, FragPos, shadowMap[1]);
        }
        else if(u_lightType == 2){ // PointLight
            outRadiance = CalcLight(u_PointLight, viewDir, normals, FragPos, Diffuse, Roughness, Metallic, F0);
        }
        else if(u_lightType == 3){ // SpotLight
            outRadiance = CalcLight(u_SpotLight, viewDir, normals, FragPos, Diffuse, Roughness, Metallic, F0);

            vec4 PosLightSpace = lightSpaceMatrix[0] * vec4(FragPos, 1.0);
            shadow = CalcShadow(PosLightSpace, u_SpotLight.direction, Normal, FragPos, shadowMap[0]);
        }

        vec3 ambient = vec3(0.00) * Diffuse; // * calcularSSAO();  // <--- Va aqui, sep
        vec3 color = ambient + outRadiance;
        color = color / (color + 1.0);
        //vec3 color = (ambient + Lo);
        //color = color / (color + vec3(1.0));
        // Gamma Correction
        color = pow(color, vec3(1.0/2.2));

        FragColor = vec4(color * shadow, 1.0);
        //FragColor = vec4(1.0);
    
    }else if(visualMode == 1){
        /*if(gl_FragCoord.x < 400){
            FragColor = vec4(normals,1.0);
        }
        if(gl_FragCoord.x >= 400 && gl_FragCoord.x < 800){
            FragColor = vec4(vec3(Specular),1.0);
        }
        if(gl_FragCoord.x >= 800 && gl_FragCoord.x < 1200){
            FragColor = vec4(vec3(Metallic),1.0);
        }
        if(gl_FragCoord.x >= 1200 && gl_FragCoord.x < 1600){
            FragColor = vec4(vec3(Roughness),1.0);
        }*/
        if(gl_FragCoord.x < 800){
            if(gl_FragCoord.y < 450){
                FragColor = vec4(normals,1.0);
            }else{
                FragColor = vec4(vec3(Specular),1.0);
            }
        }else{
            if(gl_FragCoord.y < 450){
                FragColor = vec4(vec3(Metallic),1.0);
            }else{
                FragColor = vec4(vec3(Roughness),1.0);
            }
        }
    }else if(visualMode == 2){
        //vec3 ambientOcclusion = calcularSSAO();
        //FragColor = vec4(vec3(ambientOcclusion),1.0);
    }

//    if(gl_FragCoord.x < 800){
//        if(gl_FragCoord.y < 450){
//            FragColor = vec4(vec3(Depth),1.0);
//        }else{
//            FragColor = vec4(vec3(Specular),1.0);
//        }
//    }else{
//        if(gl_FragCoord.y < 450){
//            FragColor = vec4(Normal,1.0);
//        }else{
//            FragColor = vec4(Diffuse,1.0);
//        }
//    }

}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// --------------------------------- PBR ----------------------------------
float distributionGGX(vec3 normal, vec3 halfDir, float roughness){
    float a = roughness * roughness;
    float a2 = a * a;
    float dotNH = max(dot(normal, halfDir), 0.0);
    float dotNH2 = dotNH * dotNH;

    float num = a2;
    float denom = (dotNH2 * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

float geometrySchlickGGX(float dotNV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num = dotNV;
    float denom = dotNV * (1.0 - k) + k;
    return num / denom;
}

float geometrySmith(vec3 normal, vec3 viewDir, vec3 lightDir, float roughness){

    float dotNV = max(dot(normal, viewDir),0.0);
    float dotNL = max(dot(normal, lightDir),0.0);
    float ggx2 = geometrySchlickGGX(dotNV, roughness);
    float ggx1 = geometrySchlickGGX(dotNL, roughness);
    return ggx1 * ggx2;

}

vec3 fresnelSchlick(float cosTheta, vec3 F0){
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) {
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 CalcLight(DirLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 F0){
    vec3 LightDirToObj = normalize(-light.direction);
    vec3 H = normalize(V + LightDirToObj);

    float dotNV = max(dot(N, V), 0.0);

    vec3 radiance = light.ambient * vec3(5.0); // Provisional

    float ndf = distributionGGX(N, H, Roughness);
    float thisgeometry = geometrySmith(N, V, LightDirToObj, Roughness);
    vec3 fresnel = fresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 kS = fresnel;
    vec3 kD = 1.0 - kS;
    kD *= (1.0 - Metallic);

    float dotNL = max(dot(N, LightDirToObj), 0.0);
    vec3 numerator = ndf * thisgeometry * fresnel;
    float denominator = 4.0 * dotNV * dotNL; 

    vec3 thisspecular = numerator / max(denominator,0.001);

    float spec = pow(max(dot(N, H), 0.0), 64.0);
    vec3 specularColor = vec3(0.3) * spec * light.specular; 
    vec3 specularResult = Specular * specularColor;


    return (kD * Albedo / PI + (thisspecular * specularResult)) * radiance * dotNL;
}

vec3 CalcLight(PointLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 F0){
    float distance = length(light.position - Pos);

    if(distance < light.radius){

        vec3 LightDirToObj = normalize(light.position - Pos);
        vec3 H = normalize(V + LightDirToObj);
        float dotNV = max(dot(N, V), 0.0);

        float attenuation = 1.0 / (1.0 + light.linear * distance +
    				            light.quadratic * (distance * distance));

        vec3 radiance = light.ambient * attenuation * vec3(5.0); // Provisional

        float ndf = distributionGGX(N, H, Roughness);
        float thisgeometry = geometrySmith(N, V, LightDirToObj, Roughness);
        vec3 fresnel = fresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 kS = fresnel;
        vec3 kD = 1.0 - kS;
        kD *= (1.0 - Metallic);

        float dotNL = max(dot(N, LightDirToObj), 0.0);
        vec3 numerator = ndf * thisgeometry * fresnel;
        float denominator = 4.0 * dotNV * dotNL; 

        vec3 thisspecular = numerator / max(denominator,0.001);

        float spec = pow(max(dot(N, H), 0.0), 64.0);
        vec3 specularColor = vec3(0.3) * spec * light.specular; 
        vec3 specularResult = Specular * specularColor;


        return (kD * Albedo / PI + (thisspecular * specularResult)) * radiance * dotNL;

    }
    discard;
}

vec3 CalcLight(SpotLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 F0){
    vec3 LightDirToObj = normalize(light.position - Pos);
    vec3 LightDir = normalize(-light.direction);
    vec3 H = normalize(V + LightDir);

    float dotNV = max(dot(N, V), 0.0);

    float distance = length(light.position - Pos);
    float attenuation = 1.0 / (1.0 + light.linear * distance +
    				        light.quadratic * (distance * distance));

    float theta = dot(LightDirToObj, LightDir); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);float ndf = distributionGGX(N, H, Roughness);
    float thisgeometry = geometrySmith(N, V, LightDirToObj, Roughness);
    
    vec3 radiance = light.ambient * attenuation * intensity * vec3(5.0); // Provisional
    
    vec3 fresnel = fresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 kS = fresnel;
    vec3 kD = 1.0 - kS;
    kD *= (1.0 - Metallic);

    float dotNL = max(dot(N, LightDirToObj), 0.0);
    vec3 numerator = ndf * thisgeometry * fresnel;
    float denominator = 4.0 * dotNV * dotNL; 

    vec3 thisspecular = numerator / max(denominator,0.001);

    float spec = pow(max(dot(N, H), 0.0), 64.0);
    vec3 specularColor = vec3(0.3) * spec * light.specular; 
    vec3 specularResult = Specular * specularColor;


    return (kD * Albedo / PI + (thisspecular * specularResult)) * radiance * dotNL;
}

// Shadows
float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal, vec3 objPosition, sampler2D shadowMap){
	vec3 projCoords = lightPos.xyz / lightPos.w;
	if(projCoords.z > 1.0){  return 1.0; }
	
    projCoords = (projCoords + 1.0) / 2.0;

	//float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	float angle = dot(normal, lightDir);
	if(angle >= 0){
		return 0.0;
	}

    // 0.025 - 0.0005
	float bias = max(0.008 * (1.0 - angle), 0.000005); 

	float shadow = 0.0;
    //float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y){
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 0.0 : 1.0;    
        }    
    }
    shadow /= 9.0;

	return clamp(shadow, 0.0, 1.0);
}

// Shadows PointLight
float CalcShadow(vec3 lightPos, vec3 objPosition, samplerCube shadowMap){

	vec3 projCoords = objPosition - lightPos;
	
	float closestDepth = texture(shadowMap, projCoords).r;
	closestDepth *= far_plane;
	
    float currentDepth = length(projCoords);

    float bias = 0.05;
    float shadow = currentDepth - bias > closestDepth ? 0.0 : 1.0;

	return clamp(shadow, 0.0, 1.0);
}

vec3 calcularSSAO(){

    const vec2 noiseScale = vec2(1600.0/4.0, 900.0/4.0);
    //int kernelSize = 64;
    //float radius = 0.5;
    //float bias = 0.025;

//    vec4 fragPos   = texture(gPosition, TexCoords);
//    vec3 normal    = texture(gNormal, TexCoords).rgb;
//    vec3 randomVec = normalize(texture(ssaoNoise, TexCoords * noiseScale)).xyz;  
//    
//    vec3 tangent   = normalize(randomVec - normal * dot(randomVec, normal));
//    vec3 bitangent = cross(normal, tangent);
//    mat3 TBN       = mat3(tangent, bitangent, normal);  
    
    
//    float occlusion = 0.0;
//    for(int i = 0; i < kernelSize; ++i){
//    	vec3 samplePos = TBN * samples[i];
//    	samplePos = fragPos + samplePos * radius; 
//    	
//    	vec4 offset = vec4(samplePos, 1.0);	
//    	offset      = viewMatrix * offset;
//    	offset.xyz /= offset.w;
//    	offset.xyz  = offset.xyz * 0.5 + 0.5;
//    
//    	float sampleDepth = texture(gPosition, offset.xy).z;
//    
//    	occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0);
//        //float rangeCheck = abs(fragPos.z - sampleDepth) < radius ? 1.0 : 0.0;
//        //occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;
//    }
//    //occlusion = 1.0 - (occlusion / kernelSize);
    
//    float occlusion = 0.0;
//
//    vec3 samplePos = fragPos + (TBN * vec3(1.0)) * radius;
//
//    vec4 offset = vec4(samplePos, 1.0);	
//    offset      = projMatrix * offset;
//    offset.xyz /= offset.w;
//    //offset.xyz  = offset.xyz * 0.5 + 0.5;
//
//    float sampleDepth = texture(gPosition, offset.xy).z;
//    //occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0);
//
//    return vec3(offset);

//    vec4 wordlPos   = texture(gPosition, TexCoords);
//    vec3 normal    = (viewMatrix * vec4(texture(gNormal, TexCoords).xyz, 0.0)).xyz;
//    vec3 randomVec = texture(ssaoNoise, TexCoords * noiseScale).xyz;  
//    
//    vec3 tangent   = normalize(randomVec - normal * dot(randomVec, normal));
//    vec3 binormal = cross(normal, tangent);
//    mat3 TBN       = mat3(tangent, binormal, normal);
//
//    return vec3(tangent.x);

    vec4 wordlPos   = texture(gPosition, TexCoords);

    vec3 fragPosSSAO = (viewMatrix * vec4(wordlPos.xyz, 1.0)).xyz;
    vec3 normal    = (viewMatrix * vec4(texture(gNormal, TexCoords).xyz, 0.0)).xyz;
    vec3 randomVec = texture(ssaoNoise, TexCoords * noiseScale).xyz;  
    
    vec3 tangent   = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 binormal  = cross(normal, tangent);
    mat3 TBN       = mat3(tangent, binormal, normal);
    
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; i++){
        vec3 thissample = fragPosSSAO + TBN * samples[i] * radius;
        vec4 screenSample = projMatrix * vec4(thissample, 1.0);
        screenSample.xyz /= screenSample.w;
        screenSample.xyz = screenSample.xyz * 0.5 + 0.5;

        //vec4 fragPosViewSpace = viewMatrix * vec4(FragPos, 1.0);
        //float depthValue = abs((fragPosViewSpace.z + 1.0) * 2.0);

        vec3 sampleWorldPos = texture(gPosition, screenSample.xy).xyz;
        float sampleDepth = (viewMatrix * vec4(sampleWorldPos, 1.0)).z;
        float rangeCheck = smoothstep(0.0,1.0, radius / abs(fragPosSSAO.z - sampleDepth));
        occlusion += (sampleDepth >= thissample.z + bias ? 1.0 : 0.0) * rangeCheck;

    }

    //float result = pow(1.0 - occlusion / kernelSize, intensitySSO);
    float result = 1.0 - occlusion / kernelSize;
    return vec3(result,result,result);
}