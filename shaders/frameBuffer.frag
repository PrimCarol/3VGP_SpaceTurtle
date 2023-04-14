#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
//uniform sampler2D gDepth;

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

//Cabeceras
vec4 CalcDirLight(DirLight light, vec3 normals, vec3 viewDir, vec3 Albedo, float Specular);

void main(){ 

    // ---- G-Buffer Data ----
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    //float Depth = texture(gDepth, TexCoords).r;

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

        FragColor = result;

    }else if(visualMode == 1){
        FragColor = vec4(FragPos,1.0);
    }else if(visualMode == 2){
        FragColor = vec4(Normal,1.0);
    }
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

vec4 CalcDirLight(DirLight light, vec3 normals, vec3 viewDir, vec3 Albedo, float Specular){
    vec3 lightDir = normalize(light.direction);
    
    float diff = max(dot(-lightDir, normals), 0.0);
    
    vec3 reflectDir = reflect(lightDir, normals);
    float spec = pow(max(dot(-reflectDir, viewDir), 0.0), 64); // Tendria que tenerlo el material.
    
    vec4 ambient = vec4(light.ambient,1.0) * vec4(Albedo,1.0);
    vec4 diffuse = vec4(light.diffuse, 1.0) * diff * vec4(Albedo,1.0);
    vec4 specular = vec4(light.specular, 1.0) * spec * Specular;
    
    return (ambient + diffuse + specular);
}