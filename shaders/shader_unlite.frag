#version 330

// Camera
uniform vec3 u_view_pos;

// Texture
uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;
uniform bool u_haveNormal;
uniform sampler2D u_tex_Normal;

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

void main(){
	
	vec4 TextureColor = color;
	if(u_haveAlbedo){ TextureColor = texture(u_tex_Albedo, texCoords) * color;}

	vec3 normal_ = normalize(normals);
//	if(u_haveNormal){
//		normal_ = texture(u_tex_Normal, texCoords).xyz; 
//		normal_ = normalize(normal_ * 2.0 - 1.0); 
//	}

	vec3 camera_dir = normalize(modelPosition - u_view_pos);

	vec4 result = TextureColor;

	fragColor = mix(vec4(0.5,0.5,0.5,1.0), result, visibility);
}