#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gMetalRough;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDepth;
//uniform sampler2D shadowMapping;

// Necesario
uniform vec3 viewPos;

// Extra
uniform int visualMode;

// Light Dir
struct DirLight{
	vec3 direction;

	// los colores ??
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//#define MAX_DIRECT_LIGHTS 3
//uniform int u_numDirectLights;
uniform DirLight u_DirectLight;
//uniform DirLight u_DirectLight[MAX_DIRECT_LIGHTS];

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
//#define MAX_POINT_LIGHTS 10
//uniform int u_numPointLights;
uniform PointLight u_PointLight;
//uniform PointLight u_PointLight[MAX_POINT_LIGHTS];

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
//#define MAX_SPOT_LIGHTS 4
//uniform int u_numSpotLights;
uniform SpotLight u_SpotLight;
//uniform SpotLight u_SpotLight[MAX_SPOT_LIGHTS];

// 0 -> Directional
// 1 -> Point
// 2 -> Spot
uniform int u_lightType; 

// Shadows
//uniform bool u_haveShadowMap;
uniform mat4 lightSpaceMatrix[6];
uniform sampler2D shadowMap[6];
//uniform samplerCube shadowMapPointLight;

// Cabeceras
vec4 CalcDirLight(DirLight light, vec3 normals, vec3 viewDir, vec3 Albedo, float Specular);
vec4 CalcPointLight(PointLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular);
vec4 CalcSpotLight(SpotLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular);

float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal, vec3 objPosition, sampler2D shadowMap);
float CalcShadow(vec3 lightPos, vec3 objPosition, samplerCube shadowMap);

// --- PBR ----
const float PI = 3.14159265359;
float distributionGGX(float NdotH, float roughtness);
float geometrySmith(float NdotV, float NdotL, float roughtness);
vec3 fresnelSchlick(float HdotV, vec3 baseReflectivity);

void main(){ 

    // ---- G-Buffer Data ----
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    float Metallic = texture(gMetalRough, TexCoords).r;
    float Roughness = texture(gMetalRough, TexCoords).g;
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    float Depth = texture(gDepth, TexCoords).r;

    vec3 viewDir = normalize(FragPos - viewPos);
    
    // -----------------
    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);

    vec3 baseReflectivity = mix(vec3(0.04), Diffuse, Metallic);

    vec3 Lo = vec3(0.0);
    
    vec3 lightPos = vec3(0.0); // <--- Temporal
    vec3 lightColor = vec3(1.0,0.0,0.0); // <--- Temporal

    for(int i = 0; i < 4; i++){
        vec3 L = normalize(lightPos - FragPos);
        vec3 H = normalize(V + L);

        float distance = length(lightPos - FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColor * attenuation;

        float NdotV = max(dot(N,V), 0.0000001);
        float NdotL = max(dot(N,L), 0.0000001);
        float HdotV = max(dot(H,V), 0.0);
        float NdotH = max(dot(N,H), 0.0);

        float D = distributionGGX(NdotH, Roughness);
        float G = geometrySmith(NdotV, NdotL, Roughness);
        vec3 F = fresnelSchlick(NdotV, baseReflectivity);

        vec3 specular = D * G * F;
        specular /= 4.0 * NdotV * NdotL;

        vec3 KD = vec3(1.0) - F;
        KD *= 1.0 - Metallic;

        Lo += (KD * Diffuse / PI + specular) * radiance * NdotL;
    }
    
    vec3 ambient = vec3(0.03) * Diffuse;
    
    vec3 color = ambient + Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);

    /*
    // Render
    if(visualMode == 0){
        //vec4 result = vec4(vec3(Diffuse), 1.0);
        vec4 result = vec4(vec3(Diffuse),1.0);
      
        float shadow = 1.0;

        
        //shadow = CalcShadow(PosLightSpace, Normal, FragPos, shadowMappingDirectLight);
        //if(shadow > 0.0){ //Si no esta en sombra, calculamos las luces, si hay sombra total, no lo hacemos, peque�o ahorro? }

        // Directional Lights
        if(u_lightType == 1 ){
            
            result = CalcDirLight(u_DirectLight, Normal, viewDir, Diffuse, Specular);

            // Simple Cascade Shadow
            for(int i = 0; i < 2; i++){
                vec4 PosLightSpace = lightSpaceMatrix[i] * vec4(FragPos, 1.0);
                shadow = CalcShadow(PosLightSpace, u_DirectLight.direction, Normal, FragPos, shadowMap[i]);
                result *= shadow;
            }
        }

        // Point
        else if(u_lightType == 2 ){

            result = CalcPointLight(u_PointLight, Normal, FragPos, viewDir, Diffuse, Specular);
            //shadow = CalcShadow(u_PointLight.position, FragPos, shadowMapPointLight);
//            for(int i = 0; i < 6; i++){
//                vec4 PosLightSpace = lightSpaceMatrix[i] * vec4(FragPos, 1.0);
//                shadow = CalcShadow(PosLightSpace, u_DirectLight.direction, Normal, FragPos, shadowMap[i]);
//                result *= shadow;
//            }
            result *= shadow;
        }

        // Spot
        else if(u_lightType == 3 ){
            vec4 PosLightSpace = lightSpaceMatrix[0] * vec4(FragPos, 1.0);

            result = CalcSpotLight(u_SpotLight, Normal, FragPos, viewDir, Diffuse, Specular);

            shadow = CalcShadow(PosLightSpace, u_SpotLight.direction, Normal, FragPos, shadowMap[0]);
            
            result *= shadow;
        }

        // Point Lights
//    	int CountPointLights = u_numPointLights;
//    	if(CountPointLights >= MAX_POINT_LIGHTS){ CountPointLights = MAX_POINT_LIGHTS; }
//    	for	(int i = 0; i < CountPointLights; i++){
//    		result += CalcPointLight(u_PointLight[i], Normal, FragPos, viewDir, Diffuse, Specular);
//    	}
//
//        // Spot Lights
//        int CountSpotLights = u_numSpotLights;
//        if(CountSpotLights >= MAX_SPOT_LIGHTS){ CountSpotLights = MAX_SPOT_LIGHTS; }
//        for	(int i = 0; i < CountSpotLights; i++){
//        	result += CalcSpotLight(u_SpotLight[i], Normal, FragPos, viewDir, Diffuse, Specular);
//        }

        //FragColor = result * shadow;
        FragColor = result;

    }else if(visualMode == 1){
        //FragColor = vec4(FragPos,1.0);
        FragColor = vec4(Metallic, Roughness, 0.0 ,1.0);
        //FragColor = vec4(vec3(Specular),1.0);
        //FragColor = vec4(vec3(Depth),1.0);
    }else if(visualMode == 2){
        FragColor = vec4(Normal,1.0);
    }else{
        //FragColor = vec4(color,1.0);
        FragColor = vec4(vec3(Depth),1.0);
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
    */
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
// ---------------------------------------

vec4 CalcDirLight(DirLight light, vec3 normals, vec3 viewDir, vec3 Albedo, float Specular){
    vec3 lightDir = normalize(light.direction);
    
    float diff = max(dot(-lightDir, normals), 0.0);
    
    vec3 reflectDir = reflect(lightDir, normals);
    float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // <-------

    vec4 ambient = vec4(light.ambient,1.0) * vec4(Albedo,1.0);
    vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(Albedo,1.0);
    vec4 specular = vec4(light.specular, 1.0) * spec * Specular;
    
    return (ambient + diffuse + specular);
}

vec4 CalcPointLight(PointLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular){
	
	float distance = length(light.position - objPosition);

    if(distance < light.radius){
	    vec3 lightDir = normalize(light.position - objPosition);
	    float diff = max(dot(normals, lightDir), 0.0);

	    vec3 reflectDir = reflect(-lightDir, normals);
	    float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // <-------

	    float attenuation = 1.0 / (1.0 + light.linear * distance +
							       light.quadratic * (distance * distance));

	
        vec4 ambient = vec4(light.ambient,1.0) * vec4(Albedo,1.0);
        vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(Albedo,1.0);
        vec4 specular = vec4(light.specular, 1.0) * spec * Specular;

	    ambient *= attenuation;
	    diffuse *= attenuation;
	    specular *= attenuation;

	    return (ambient + diffuse + specular);
    }
    discard;   
}

vec4 CalcSpotLight(SpotLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular){
    vec3 lightDir = normalize(light.position - objPosition);
	float diff = max(dot(normals, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normals);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // <-------

	float distance = length(light.position - objPosition);
	float attenuation = 1.0 / (1.0 + light.linear * distance +
							   light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec4 ambient = vec4(light.ambient,1.0) * vec4(Albedo,1.0);
    vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(Albedo,1.0);
    vec4 specular = vec4(light.specular, 1.0) * spec * Specular;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

// Shadows
float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal, vec3 objPosition, sampler2D shadowMap){
    //vec3 lightDir = normalize(objPosition - lightPos.xyz);
	vec3 projCoords = lightPos.xyz / lightPos.w;
	if(projCoords.z > 1.0){  return 1.0; }
	
    projCoords = (projCoords + 1.0) / 2.0;

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	
    //float bias = 0.005;
	float angle = dot(normal, lightDir);
	if(angle >= 0){
		return 0.0;
	}

	float bias = max(0.025 * (1.0 - angle), 0.0005); 

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