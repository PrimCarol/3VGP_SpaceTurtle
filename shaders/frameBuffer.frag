#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
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

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//#define MAX_POINT_LIGHTS 10
//uniform int u_numPointLights;
uniform PointLight u_PointLight;
//uniform PointLight u_PointLight[MAX_POINT_LIGHTS];

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;
  
    float constant;
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
uniform mat4 lightSpaceMatrix;
uniform sampler2D shadowMap[6];
//uniform sampler2D shadowMappingPointLight[6];

// Cabeceras
vec4 CalcDirLight(DirLight light, vec3 normals, vec3 viewDir, vec3 Albedo, float Specular);
vec4 CalcPointLight(PointLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular);
vec4 CalcSpotLight(SpotLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular);

float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal, vec3 objPosition, sampler2D shadowMap);

void main(){ 

    // ---- G-Buffer Data ----
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    float Depth = texture(gDepth, TexCoords).r;

    vec3 viewDir = normalize(FragPos - viewPos);

    // Render
    if(visualMode == 0){
        //vec4 result = vec4(vec3(Diffuse), 1.0);
        vec4 result = vec4(vec3(Diffuse),1.0);
      
        float shadow = 1.0;

        vec4 PosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
        //shadow = CalcShadow(PosLightSpace, Normal, FragPos, shadowMappingDirectLight);
        //if(shadow > 0.0){ //Si no esta en sombra, calculamos las luces, si hay sombra total, no lo hacemos, pequeño ahorro? }

        // Directional Lights
        if(u_lightType == 1 ){
            result = CalcDirLight(u_DirectLight, Normal, viewDir, Diffuse, Specular);

            shadow = CalcShadow(PosLightSpace, u_DirectLight.direction, Normal, FragPos, shadowMap[0]);
        }

        // Point
        if(u_lightType == 2 ){
            result = CalcPointLight(u_PointLight, Normal, FragPos, viewDir, Diffuse, Specular);
        }

        // Spot
        if(u_lightType == 3 ){
            result = CalcSpotLight(u_SpotLight, Normal, FragPos, viewDir, Diffuse, Specular);

            shadow = CalcShadow(PosLightSpace, u_SpotLight.direction, Normal, FragPos, shadowMap[0]);
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

        FragColor = result * shadow;

    }else if(visualMode == 1){
        FragColor = vec4(FragPos,1.0);
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
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

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
	
	vec3 lightDir = normalize(light.position - objPosition);
	float diff = max(dot(normals, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normals);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // <-------

	float distance = length(light.position - objPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
							   light.quadratic * (distance * distance));

	
    vec4 ambient = vec4(light.ambient,1.0) * vec4(Albedo,1.0);
    vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(Albedo,1.0);
    vec4 specular = vec4(light.specular, 1.0) * spec * Specular;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec4 CalcSpotLight(SpotLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular){
    vec3 lightDir = normalize(light.position - objPosition);
	float diff = max(dot(normals, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normals);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // <-------

	float distance = length(light.position - objPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
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
//	if(angle >= 0){
//		return 0.0;
//	}

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