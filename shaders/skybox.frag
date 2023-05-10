#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube u_tex_Albedo;

void main(){    
    //FragColor = vec4(1.0,0.0,0.0,1.0);
    FragColor = texture(u_tex_Albedo, TexCoords);
}