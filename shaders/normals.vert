#version 330
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

layout (location = 3) in mat4 instance_Matrix;

out VS_OUT {
    vec3 normal;
} vs_out;

// Basic Info
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_vp_matrix;

void main(){
    gl_Position = u_view_matrix * instance_Matrix * vec4(a_position, 1.0); 
    mat3 normalMatrix = mat3(transpose(inverse(u_view_matrix * instance_Matrix)));
    vs_out.normal = normalize(vec3(vec4(normalMatrix * a_normal, 0.0)));
}