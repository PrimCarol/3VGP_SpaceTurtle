#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube u_tex_Albedo;

void main(){    
    FragColor = texture(u_tex_Albedo, TexCoords);
}