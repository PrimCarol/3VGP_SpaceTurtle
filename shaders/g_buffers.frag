#version 330 core
layout (location = 0) out vec4 gAlbedoSpec;
layout (location = 1) out vec2 gMetalRough;
layout (location = 2) out vec3 gPosition;
layout (location = 3) out vec3 gNormal;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in float Roughness;
in float Metallic;

in vec4 color;

uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;
uniform bool u_haveSpecular;
uniform sampler2D u_tex_Specular;
uniform bool u_haveNormal;
uniform sampler2D u_tex_Normal;
uniform bool u_haveRoughness;
uniform sampler2D u_tex_Roughness;
uniform bool u_haveMetallic;
uniform sampler2D u_tex_Metallic;

void main(){
    
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
    
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);
    if(u_haveNormal){ gNormal = texture(u_tex_Normal, TexCoords).rgb;}

    // and the diffuse per-fragment color
    vec4 TextureColor = color;
    gAlbedoSpec = color;
	if(u_haveAlbedo){ gAlbedoSpec.rgb = (texture(u_tex_Albedo, TexCoords) * color).rgb;}

    // store specular intensity in gAlbedoSpec's alpha component
	gAlbedoSpec.a = 1.0;
	if(u_haveSpecular){	gAlbedoSpec.a = texture(u_tex_Specular, TexCoords).r;}

    gMetalRough.r = Metallic; // Metalic 0.0 a 1.0
    if(u_haveMetallic){ gMetalRough.r = texture(u_tex_Metallic, TexCoords).r; }

    gMetalRough.g = Roughness; // Roughtness 0.1 a 1.0
    if(Roughness < 0.1){gMetalRough.g = 0.1;}
    if(u_haveRoughness){ gMetalRough.g = texture(u_tex_Roughness, TexCoords).r; }

    //
}