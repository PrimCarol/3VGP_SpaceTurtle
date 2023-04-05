#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec4 color;

uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;
uniform bool u_haveSpecular;
uniform sampler2D u_tex_Specular;

void main(){
    
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
    
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);

    // and the diffuse per-fragment color
    vec4 TextureColor = color;
	if(u_haveAlbedo){ gAlbedoSpec.rgb = (texture(u_tex_Albedo, TexCoords) * color).rgb;}

    // store specular intensity in gAlbedoSpec's alpha component
	vec4 TextureSpecular = vec4(1.0,1.0,1.0,1.0);
	if(u_haveSpecular){	gAlbedoSpec.a = texture(u_tex_Specular, TexCoords).r;}
}