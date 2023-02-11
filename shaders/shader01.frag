#version 330

// Camera
uniform vec3 u_view_pos;

// Texture
uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;

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
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec);

void main(){
	
	vec4 TextureColor = texture(u_tex_Albedo, texCoords);

	//vec4 TextureSpecular = texture(u_specularTexture, texCoords);
	vec4 TextureSpecular = vec4(1.0,1.0,1.0,1.0);

	vec3 normal_ = normalize(normals);
	vec3 camera_dir = normalize(modelPosition - u_view_pos);

//	vec4 result;
//	if(u_haveAlbedo){ result = (TextureColor * color); }
//	else { result = color; }

	DirLight myDirLight;
	myDirLight.direction = vec3(1.0,-0.5,0.0);
	myDirLight.ambient = vec3(0.4,0.4,0.4);
	myDirLight.diffuse = vec3(1.0,1.0,1.0);
	myDirLight.specular = vec3(1.0,1.0,1.0);
	//vec4 result = CalcDirLight(myDirLight, normal_, camera_dir, TextureColor, TextureSpecular);
	vec4 result = CalcDirLight(u_DirectLight, normal_, camera_dir, TextureColor, TextureSpecular);

//	// Point Lights
//	int CountPointLights = u_numPointLights;
//	if(CountPointLights >= MAX_POINT_LIGHTS){ CountPointLights = MAX_POINT_LIGHTS; }
//	for	(int i = 0; i < CountPointLights; i++){
//		result += CalcPointLight(u_PointLight[i], normal_, modelPosition, camera_dir, TextureColor, TextureSpecular);
//	}
//	
//	// Spot Lights
//	int CountSpotLights = u_numSpotLights;
//	if(CountSpotLights >= MAX_SPOT_LIGHTS){ CountSpotLights = MAX_SPOT_LIGHTS; }
//	for	(int i = 0; i < CountSpotLights; i++){
//		result += CalcSpotLight(u_SpotLight[i], normal_, modelPosition, camera_dir, TextureColor, TextureSpecular);
//	}

	//fragColor = mix(u_FogColor, vec4(result, 1.0), visibility);
	
	fragColor = mix(vec4(0.5,0.5,0.5,1.0), result * color, visibility);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
	vec3 lightDir = normalize(light.direction);

	float diff = max(dot(-lightDir, normal), 0.0);

	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // Tendria que tenerlo el material.

	vec4 ambient = vec4(light.ambient,1.0) * TexDiff;
	vec4 diffuse = vec4(light.diffuse, 1.0) * diff * TexDiff;
	vec4 specular = vec4(light.specular,1.0) * spec  * TexSpec;

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
	
	vec3 lightDir = normalize(light.position - modelPos);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // <-------

	float distance = length(light.position - modelPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
							   light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(TexDiff);
	vec3 diffuse = light.diffuse * diff * vec3(TexDiff);
	vec3 specular = light.specular * spec * vec3(TexSpec);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 modelPos, vec3 viewDir, vec4 TexDiff, vec4 TexSpec){
    vec3 lightDir = normalize(light.position - modelPos);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64.0); // <-------

	float distance = length(light.position - modelPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
							   light.quadratic * (distance * distance));

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * vec3(TexDiff);
	vec3 diffuse = light.diffuse * diff * vec3(TexDiff);
	vec3 specular = light.specular * spec * vec3(TexSpec);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}