#version 330 core
// Mesh
layout (location=0) in vec3 a_position;
// Instancing Transformations
layout (location = 3) in mat4 instance_Matrix;

uniform mat4 lightSpaceMatrix;

void main(){
    gl_Position = lightSpaceMatrix * instance_Matrix * vec4(a_position, 1.0);
}