#version 330

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

	vec4 result = TextureColor;

	fragColor = mix(vec4(0.5,0.5,0.5,1.0), result, visibility);
}