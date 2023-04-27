#version 330 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

// Shadow Mapping
//out vec4 FragPosLightSpace;
//uniform mat4 lightSpaceMatrix;

void main(){

    // ---- Shadow Mapping -----
	//FragPosLightSpace = lightSpaceMatrix * vec4(u_viewPos, 1.0);

    gl_Position = vec4(a_position.x, a_position.y, 0.0, 1.0); 
    TexCoords = aTexCoords;
}  