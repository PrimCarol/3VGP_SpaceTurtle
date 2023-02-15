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
uniform DirLight u_DirectLight;

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
uniform int u_numPointLights = 0;
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
uniform int u_numSpotLights = 0;
uniform SpotLight u_SpotLight[MAX_SPOT_LIGHTS];

// Fog
uniform vec4 u_FogColor;

uniform float u_shininess;

// Basic In
in vec3 modelPosition;
in vec4 color;
in vec3 normals;
in vec2 texCoords;

// Fog In
in float visibility;

out vec4 fragColor;

//Cabeceras
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);

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

	//vec4 result = CalcDirLight(myDirLight, normal_, camera_dir, TextureColor, TextureSpecular);
	vec4 result = CalcDirLight(u_DirectLight, normal_, camera_dir, TextureColor, TextureSpecular);

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
	
	fragColor = mix(vec4(0.5,0.5,0.5,1.0), result, visibility);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
	vec3 lightDir = normalize(light.direction);

	float diff = max(dot(-lightDir, normal), 0.0);

	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), u_shininess); // Tendria que tenerlo el material.

	vec4 ambient = vec4(light.ambient,1.0) * TexDiff;
	vec4 diffuse = vec4(light.diffuse, 1.0) * diff * TexDiff;
	vec4 specular = vec4(light.specular, 1.0) * spec  * TexSpec;

	return (ambient + diffuse + specular);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
	
	vec3 lightDir = normalize(light.position - modelPos);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), u_shininess); // <-------

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
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), u_shininess); // <-------

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