#version 330

// Camera
uniform vec3 u_view_pos;

// Texture
uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;
uniform bool u_haveSpecular;
uniform sampler2D u_tex_Specular;
uniform bool u_haveNormal;
uniform sampler2D u_tex_Normal;

// Light Dir
struct DirLight{
	vec3 direction;

	// los colores ??
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define MAX_DIRECT_LIGHTS 3
uniform int u_numDirectLights;
uniform DirLight u_DirectLight[MAX_DIRECT_LIGHTS];

struct PointLight{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define MAX_POINT_LIGHTS 10
uniform int u_numPointLights;
uniform PointLight u_PointLight[MAX_POINT_LIGHTS];

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
#define MAX_SPOT_LIGHTS 4
uniform int u_numSpotLights;
uniform SpotLight u_SpotLight[MAX_SPOT_LIGHTS];

// Fog
uniform vec4 u_FogColor;

// Material
in float shininess;

// Basic In
in vec3 modelPosition;
in vec4 color;
in vec3 normals;
in vec2 texCoords;

// Shadow Mapping
uniform bool u_haveShadowMap;
in vec4 FragPosLightSpace;
uniform sampler2D shadowMap;

// Fog In
in float visibility;

out vec4 fragColor;

//Cabeceras
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);
//float CalcShadow(float dotLightNormal);
float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal);

void main(){
	
	vec4 TextureColor = color;
	if(u_haveAlbedo){ TextureColor = texture(u_tex_Albedo, texCoords) * color;}

	vec4 TextureSpecular = vec4(1.0,1.0,1.0,1.0);
	if(u_haveSpecular){	TextureSpecular = texture(u_tex_Specular, texCoords);}

	vec3 normal_ = normalize(normals);
//	if(u_haveNormal){
//		normal_ = texture(u_tex_Normal, texCoords).xyz; 
//		normal_ = normalize(normal_ * 2.0 - 1.0); 
//	}

	vec3 camera_dir = normalize(modelPosition - u_view_pos);

	// -------- Calculo del Color/Luz --------
	vec4 result = vec4(0.0);

	// Directional Lights
	if(u_numDirectLights == 0 ){
		DirLight noDirectional;
		noDirectional.direction = vec3(0.0);
		noDirectional.ambient = vec3(0.1);
		noDirectional.diffuse = vec3(0.0);
		noDirectional.specular = vec3(0.0);
		result += CalcDirLight(noDirectional, normal_, camera_dir, TextureColor, TextureSpecular);
	}else{
		int CountDirectLights = u_numDirectLights;
		if(CountDirectLights >= MAX_DIRECT_LIGHTS){ CountDirectLights = MAX_DIRECT_LIGHTS; }
		for(int i = 0; i < CountDirectLights; i++){
			result += CalcDirLight(u_DirectLight[i], normal_, camera_dir, TextureColor, TextureSpecular);
		}
	}

	// Shadow Mapping ------ TEMPORAL --------
	float shadow = 1.0;
	if(u_haveShadowMap){
//		float dotLightTemp = dot(u_DirectLight[0].direction, normal_);
//		shadow = CalcShadow(dotLightTemp);
		shadow = CalcShadow(FragPosLightSpace, u_DirectLight[0].direction, normal_);
	}

	// Point Lights
	int CountPointLights = u_numPointLights;
	if(CountPointLights >= MAX_POINT_LIGHTS){ CountPointLights = MAX_POINT_LIGHTS; }
	for	(int i = 0; i < CountPointLights; i++){
		result += CalcPointLight(u_PointLight[i], normal_, modelPosition, camera_dir, TextureColor, TextureSpecular);
	}
	
	// Spot Lights
	int CountSpotLights = u_numSpotLights;
	if(CountSpotLights >= MAX_SPOT_LIGHTS){ CountSpotLights = MAX_SPOT_LIGHTS; }
	for	(int i = 0; i < CountSpotLights; i++){
		result += CalcSpotLight(u_SpotLight[i], normal_, modelPosition, camera_dir, TextureColor, TextureSpecular);
	}

	//fragColor = mix(u_FogColor, vec4(result, 1.0), visibility);
	
	//fragColor = mix(vec4(0.5,0.5,0.5,1.0), result * shadow, visibility);
	fragColor = result * shadow;
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
	vec3 lightDir = normalize(light.direction);

	float diff = max(dot(-lightDir, normal), 0.0);

	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), shininess); // Tendria que tenerlo el material.

	vec4 ambient = vec4(light.ambient,1.0) * TexDiff;
	vec4 diffuse = vec4(light.diffuse, 1.0) * diff * TexDiff;
	vec4 specular = vec4(light.specular, 1.0) * spec  * TexSpec;

	return (ambient + diffuse + specular);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
	
	vec3 lightDir = normalize(light.position - modelPos);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), shininess); // <-------

	float distance = length(light.position - modelPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
							   light.quadratic * (distance * distance));

	
	vec4 ambient;
	vec4 diffuse;

	if(u_haveAlbedo){
		ambient = vec4(light.ambient,1.0) * (TexDiff * color);
		diffuse = vec4(light.diffuse, 1.0) * diff * (TexDiff * color);
	}else{
		ambient = vec4(light.ambient,1.0) * color;
		diffuse = vec4(light.diffuse, 1.0) * diff * color;
	}
	vec4 specular = vec4(light.specular, 1.0) * spec * TexSpec;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
    vec3 lightDir = normalize(light.position - modelPos);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), shininess); // <-------

	float distance = length(light.position - modelPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
							   light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec4 ambient;
	vec4 diffuse;

    if(u_haveAlbedo){
		ambient = vec4(light.ambient,1.0) * (TexDiff * color);
		diffuse = vec4(light.diffuse, 1.0) * diff * (TexDiff * color);
	}else{
		ambient = vec4(light.ambient,1.0) * color;
		diffuse = vec4(light.diffuse, 1.0) * diff * color;
	}
	vec4 specular = vec4(light.specular, 1.0) * spec * TexSpec;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

//float CalcShadow(float dotLightNormal){
//	
//	vec3 pos = FragPosLightSpace.xyz * 0.5 + 0.5;
//	if(pos.z > 1.0){ pos.z = 1.0; }
//
//	if(dotLightNormal > 1 ){return 0.0;}
//
//	//float bias = max(0.0005 * (1.0 - dotLightNormal), 0.0);
//	float bias = 0.05;
//
//	float returnShadow = 0.0;
////	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
////	for(int x = -1; x <= 1; ++x){
////		for(int y = -1; y <= 1; ++y){
////			float depth = texture(shadowMap, pos.xy + vec2(x,y) * texelSize).r;
////			returnShadow += (depth + bias) < pos.z ? 0.0 : 1.0;
////			
////		}
////	}
////	returnShadow /= 9;
//	float depth = texture(shadowMap, pos.xy).r;
//	returnShadow += (depth + bias) < pos.z ? 0.0 : 1.0;
//	
//	return returnShadow;
//}

float CalcShadow(vec4 lightPos, vec3 lightDir, vec3 normal){
	vec3 projCoords = lightPos.xyz / lightPos.w;
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	
	//float bias = 0.005;
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 

	return currentDepth - bias < closestDepth  ? 1.0 : 0.0; 
}