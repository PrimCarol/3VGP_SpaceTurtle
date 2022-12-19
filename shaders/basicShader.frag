#version 330 core

out vec4 FragColor;

// Fog In
vec4 u_FogColor = vec4(0.2, 0.2, 0.2,1.0);
in float visibility;

in vec3 color;
in vec3 normals;
in vec2 texCoords;

// Texture
uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;

void main(){

	vec3 normal_ = normalize(normals);
	vec4 TextureColor = texture(u_tex_Albedo, texCoords);

    // ---- Color Base/Textura -----	
	vec3 albedo;
	if(u_haveAlbedo){ albedo = (TextureColor * vec4(color, 1.0)).xyz; }
	else { albedo = vec4(color, 1.0).xyz ; }
    
	
	FragColor = mix(u_FogColor, vec4(albedo,1.0), visibility);
}