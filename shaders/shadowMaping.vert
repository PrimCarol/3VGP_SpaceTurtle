#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 u_m_trans;

void main(){
    gl_Position = lightSpaceMatrix * u_m_trans * vec4(aPos, 1.0);
}