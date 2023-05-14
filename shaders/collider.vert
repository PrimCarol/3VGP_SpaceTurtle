#version 330
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

layout (location = 3) in mat4 instance_Matrix;

uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

//// Basic Info
//
//uniform vec3 u_minColliderPos;
//uniform vec3 u_maxColliderPos;
//
//out vec3 minColliderPos;
//out vec3 maxColliderPos;
//
//out mat4 modelMatrix;
//
//void main(){
//    modelMatrix = instance_Matrix;
//    gl_Position = u_projection_matrix * u_view_matrix * instance_Matrix * vec4(a_position, 1.0);
//}

out vec3 fragPosition;

void main()
{
    gl_Position = u_projection_matrix * u_view_matrix * instance_Matrix * vec4(a_position, 1.0);
    fragPosition = vec3(instance_Matrix * vec4(a_position, 1.0));
}