#version 330

out vec4 FragColor;

// Camera
uniform vec3 u_view_pos;

in vec3 color;
in vec3 normals;
in vec2 texCoords;

in vec3 modelPosition;

// Texture
uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;


void main() { 
	
	vec3 normal_ = normalize(normals);

	vec4 TextureColor = texture(u_tex_Albedo, texCoords);

	if(u_haveAlbedo){ FragColor = TextureColor * vec4(color, 1.0); }
	else { FragColor = vec4(color, 1.0); }
}