#version 330 core
// Mesh
layout (location=0) in vec3 a_position;
// Instancing Transformations
layout (location = 3) in mat4 instance_Matrix;

uniform mat4 u_lightSpaceMatrix;
uniform int u_lightType;

out int lightType;

void main(){
    lightType = u_lightType;
    gl_Position = u_lightSpaceMatrix * instance_Matrix * vec4(a_position, 1.0);
}