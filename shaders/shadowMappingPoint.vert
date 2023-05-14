#version 330

// Mesh
layout (location=0) in vec3 a_position;
// Instancing Transformations
layout (location = 3) in mat4 instance_Matrix;

void main(){
    gl_Position = instance_Matrix * vec4(a_position, 1.0);
}