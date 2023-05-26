#version 330 core
// Mesh
layout (location = 0) in vec3 a_position;
// Instancing Transformations
layout (location = 5) in mat4 instance_Matrix;

uniform mat4 u_lightSpaceMatrix;

void main(){
    gl_Position = u_lightSpaceMatrix * instance_Matrix * vec4(a_position, 1.0);
}