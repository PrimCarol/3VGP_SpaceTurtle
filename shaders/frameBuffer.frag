#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDepth;
//uniform sampler2D shadowMapping;

// Extra
uniform int visualMode;

// Necesario
uniform vec3 viewPos;

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

//Cabeceras
vec4 CalcDirLight(DirLight light, vec3 normals, vec3 viewDir, vec3 Albedo, float Specular);
vec4 CalcPointLight(PointLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular);
vec4 CalcSpotLight(SpotLight light, vec3 normals, vec3 objPosition, vec3 viewDir, vec3 Albedo, float Specular);

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
        vec4 result = vec4(0.0);
      
        // Directional Lights
        if(u_numDirectLights == 0 ){
        	DirLight noDirectional;
        	noDirectional.direction = vec3(0.0);
        	noDirectional.ambient = vec3(0.1);
        	noDirectional.diffuse = vec3(0.0);
        	noDirectional.specular = vec3(0.0);
        	result += CalcDirLight(noDirectional, Normal, viewDir, Diffuse, Specular);
        }else{
        	int CountDirectLights = u_numDirectLights;
        	if(CountDirectLights >= MAX_DIRECT_LIGHTS){ CountDirectLights = MAX_DIRECT_LIGHTS; }
        	for(int i = 0; i < CountDirectLights; i++){
        		result += CalcDirLight(u_DirectLight[i], Normal, viewDir, Diffuse, Specular);
        	}
        }

        // Point Lights
    	int CountPointLights = u_numPointLights;
    	if(CountPointLights >= MAX_POINT_LIGHTS){ CountPointLights = MAX_POINT_LIGHTS; }
    	for	(int i = 0; i < CountPointLights; i++){
    		result += CalcPointLight(u_PointLight[i], Normal, FragPos, viewDir, Diffuse, Specular);
    	}

        // Spot Lights
        int CountSpotLights = u_numSpotLights;
        if(CountSpotLights >= MAX_SPOT_LIGHTS){ CountSpotLights = MAX_SPOT_LIGHTS; }
        for	(int i = 0; i < CountSpotLights; i++){
        	result += CalcSpotLight(u_SpotLight[i], Normal, FragPos, viewDir, Diffuse, Specular);
        }

        FragColor = result;

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