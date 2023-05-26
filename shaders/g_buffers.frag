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

in mat3 TBN;

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
    
    gPosition = FragPos;
    
    // NORMALS
    //gNormal = normalize(Normal);
    //if(u_haveNormal){ gNormal = texture(u_tex_Normal, TexCoords).rgb;}
    //gNormal = gNormal * 0.5 + 0.5;

    vec3 normal = normalize(Normal);
    if(u_haveNormal){
        normal = texture(u_tex_Normal, TexCoords).rgb;
        normal = normalize(TBN * (normal * 2.0 - 1.0));
    }else{
        normal = normal * 0.5 + 0.5;
    }
    gNormal = normal;

    // COLOR
    vec4 TextureColor = color;
    gAlbedoSpec = color;
	if(u_haveAlbedo){ gAlbedoSpec.rgb = (pow(texture(u_tex_Albedo, TexCoords), vec4(vec3(2.2),1.0)) * color).rgb;}

    // SPECULAR
	gAlbedoSpec.a = 1.0;
	if(u_haveSpecular){	gAlbedoSpec.a = texture(u_tex_Specular, TexCoords).r;}

    // METALLIC
    gMetalRough.r = Metallic; // Metalic 0.0 a 1.0
    if(u_haveMetallic){ gMetalRough.r = texture(u_tex_Metallic, TexCoords).r; }

    // ROUGHNESS
    gMetalRough.g = Roughness; // Roughtness 0.1 a 1.0
    if(Roughness < 0.1){gMetalRough.g = 0.1;}
    if(u_haveRoughness){ gMetalRough.g = texture(u_tex_Roughness, TexCoords).r; }
}