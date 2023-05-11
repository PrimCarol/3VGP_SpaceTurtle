#version 330
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

layout (location = 3) in mat4 instance_Matrix;

// Basic Info
uniform mat4 u_view_matrix;

uniform vec3 u_minColliderPos;
uniform vec3 u_maxColliderPos;

out vec3 minColliderPos;
out vec3 maxColliderPos;

void main(){
    gl_Position = u_view_matrix * instance_Matrix * vec4(a_position, 1.0);
    mat3 normalMatrix = mat3(transpose(inverse(u_view_matrix * instance_Matrix)));
    minColliderPos = normalize(vec3(vec4(normalMatrix * u_minColliderPos, 0.0)));
    maxColliderPos = normalize(vec3(vec4(normalMatrix * u_maxColliderPos, 0.0)));
}