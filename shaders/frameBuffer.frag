#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gMetalRough;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDepth;
uniform samplerCube gSkybox;

// Necesario
uniform vec3 viewPos;

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

// Cabeceras
vec3 CalcLight(PointLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 baseReflectivity);
vec3 CalcLight(DirLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 baseReflectivity);
vec3 CalcLight(SpotLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 baseReflectivity);

float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal, vec3 objPosition, sampler2D shadowMap);
float CalcShadow(vec3 lightPos, vec3 objPosition, samplerCube shadowMap);

// --- PBR ----
const float PI = 3.14159265359;
float distributionGGX(float NdotH, float roughtness);
float geometrySmith(float NdotV, float NdotL, float roughtness);
vec3 fresnelSchlick(float HdotV, vec3 baseReflectivity);

float Specular;

void main(){ 

    // ---- G-Buffer Data ----
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    Specular = texture(gAlbedoSpec, TexCoords).a;
    float Metallic = texture(gMetalRough, TexCoords).r;
    float Roughness = texture(gMetalRough, TexCoords).g;
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    float Depth = texture(gDepth, TexCoords).r;
    
    float shadow = 1.0;

    // -----------------
    vec3 normals = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Aqui iria el skybox? en el primer MIX
    vec3 reflectDir = reflect(viewDir, normals);
    vec3 skyboxColor = texture(gSkybox, -reflectDir).rgb;
    vec3 baseReflectivity = mix(skyboxColor, Diffuse, 1.0 - Metallic);

    vec3 Lo = vec3(0.0);

    if(visualMode == 0){
        if(u_lightType == 1){ // DirLight
            Lo = CalcLight(u_DirectLight, viewDir, normals, FragPos, Diffuse, Roughness, Metallic, baseReflectivity);
        
            vec4 PosLightSpaceHigh = lightSpaceMatrix[0] * vec4(FragPos, 1.0);
            shadow = CalcShadow(PosLightSpaceHigh, u_DirectLight.direction, Normal, FragPos, shadowMap[0]);

            /*if(shadow == 1.0){
                vec4 PosLightSpaceMedium = lightSpaceMatrix[1] * vec4(FragPos, 1.0);
                shadow = CalcShadow(PosLightSpaceMedium, u_DirectLight.direction, Normal, FragPos, shadowMap[1]);
            }

            if(shadow == 1.0){
                vec4 PosLightSpaceLow = lightSpaceMatrix[2] * vec4(FragPos, 1.0);
                shadow = CalcShadow(PosLightSpaceLow, u_DirectLight.direction, Normal, FragPos, shadowMap[2]);
            }*/
        }
        else if(u_lightType == 2){ // PointLight
            Lo = CalcLight(u_PointLight, viewDir, normals, FragPos, Diffuse, Roughness, Metallic, baseReflectivity);
        }
        else if(u_lightType == 3){ // SpotLight
            Lo = CalcLight(u_SpotLight, viewDir, normals, FragPos, Diffuse, Roughness, Metallic, baseReflectivity);

            vec4 PosLightSpace = lightSpaceMatrix[0] * vec4(FragPos, 1.0);
            shadow = CalcShadow(PosLightSpace, u_SpotLight.direction, Normal, FragPos, shadowMap[0]);
        }

        vec3 ambient = vec3(0.0) * Diffuse; 
        vec3 color = ambient + Lo;
        color = color / (color + vec3(1.0));
        // Gamma Correction
        color = pow(color, vec3(1.0/2.2));

        FragColor = vec4(color * shadow, 1.0);
    
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
float distributionGGX(float NdotH, float roughtness){
    float a = roughtness * roughtness;
    float a2 = a*a;
    float denom = NdotH * NdotH * (a2 - 1.0) + 1.0;
    denom = PI * denom * denom;
    return a2 / max(denom, 0.0000001);
}

float geometrySmith(float NdotV, float NdotL, float roughtness){
    float r = roughtness + 1.0;
    float k = (r*r) / 8.0;
    float ggx1 = NdotV / (NdotV * (1.0 - k) + k);
    float ggx2 = NdotL / (NdotL * (1.0 - k) + k);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float HdotV, vec3 baseReflectivity){
    return baseReflectivity + (1.0 - baseReflectivity) * pow(1.0 - HdotV, 5.0);
}

vec3 CalcLight(DirLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 baseReflectivity){
    vec3 LightDirToObj = normalize(-light.direction);
    vec3 H = normalize(V + LightDirToObj);

    vec3 radiance = light.ambient;

    float NdotV = max(dot(N,V), 0.0000001);
    float NdotL = max(dot(N,LightDirToObj), 0.0000001);
    float HdotV = max(dot(H,V), 0.0);
    float NdotH = max(dot(N,H), 0.0);

    float D = distributionGGX(NdotH, Roughness);
    float G = geometrySmith(NdotV, NdotL, Roughness);
    vec3 F = fresnelSchlick(NdotV, baseReflectivity);

    vec3 specular = D * G * F * Specular;
    specular /= 1.0 * NdotV * NdotL;

    vec3 KD = vec3(1.0) - F;
    KD *= 1.0 - Metallic;

    return (KD * Albedo / PI + specular) * radiance * NdotL;

    // IBL
    //vec3 directLighting = (KD * Albedo / PI + specular) * radiance * NdotL;
    //vec3 R = reflect(-V, N);
    //vec3 prefilteredColor = textureLod(gSkybox, R, Roughness * 5.0).rgb;
    //vec3 indirectSpecular = prefilteredColor * F * D * G;
    //vec3 indirectDiffuse = texture(gSkybox, N).rgb * Albedo / PI;
    //
    //return directLighting + indirectDiffuse + indirectSpecular;
}

vec3 CalcLight(PointLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 baseReflectivity){
    float distance = length(light.position - Pos);

    if(distance < light.radius){
        vec3 LightDirToObj = normalize(light.position - Pos);
        vec3 H = normalize(V + LightDirToObj);

        float attenuation = 1.0 / (1.0 + light.linear * distance +
							        light.quadratic * (distance * distance));
        vec3 radiance = light.ambient * attenuation;

        float NdotV = max(dot(N,V), 0.0000001);
        float NdotL = max(dot(N,LightDirToObj), 0.0000001);
        float HdotV = max(dot(H,V), 0.0);
        float NdotH = max(dot(N,H), 0.0);

        float D = distributionGGX(NdotH, Roughness);
        float G = geometrySmith(NdotV, NdotL, Roughness);
        vec3 F = fresnelSchlick(NdotV, baseReflectivity);

        vec3 specular = D * G * F * Specular;
        specular /= 1.0 * NdotV * NdotL;

        vec3 KD = vec3(1.0) - F;
        KD *= 1.0 - Metallic;

        return (KD * Albedo / PI + specular) * radiance * NdotL;
    }
    discard;
}

vec3 CalcLight(SpotLight light, vec3 V, vec3 N, vec3 Pos, vec3 Albedo, float Roughness, float Metallic, vec3 baseReflectivity){
    vec3 LightDirToObj = normalize(light.position - Pos);
    vec3 LightDir = normalize(-light.direction);
    vec3 H = normalize(V + LightDir);

    float distance = length(light.position - Pos);
    float attenuation = 1.0 / (1.0 + light.linear * distance +
							    light.quadratic * (distance * distance));

    float theta = dot(LightDirToObj, LightDir); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 radiance = light.ambient * attenuation * intensity;

    float NdotV = max(dot(N,V), 0.0000001);
    float NdotL = max(dot(N,LightDir), 0.0000001);
    float HdotV = max(dot(H,V), 0.0);
    float NdotH = max(dot(N,H), 0.0);

    float D = distributionGGX(NdotH, Roughness);
    float G = geometrySmith(NdotV, NdotL, Roughness);
    vec3 F = fresnelSchlick(NdotV, baseReflectivity);

    vec3 specular = D * G * F * Specular;
    specular /= 1.0 * NdotV * NdotL;

    vec3 KD = vec3(1.0) - F;
    KD *= 1.0 - Metallic;

    return (KD * Albedo / PI + specular) * radiance * NdotL;
}

// Shadows
float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal, vec3 objPosition, sampler2D shadowMap){
	vec3 projCoords = lightPos.xyz / lightPos.w;
	if(projCoords.z > 1.0){  return 1.0; }
	
    projCoords = (projCoords + 1.0) / 2.0;

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	float angle = dot(normal, lightDir);
	if(angle >= 0){
		return 0.0;
	}

    // 0.025 - 0.0005
	float bias = max(0.008 * (1.0 - angle), 0.000005); 

	float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
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