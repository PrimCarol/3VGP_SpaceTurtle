#version 330
layout (triangles) in;
layout (line_strip, max_vertices = 16) out;
 

in mat4 modelMatrix;

uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

uniform vec3 u_minColliderPos;
uniform vec3 u_maxColliderPos;

in vec3 fragPosition[];

void main(){

    vec3 min = gl_in[0].gl_Position.xyz;
    vec3 max = gl_in[1].gl_Position.xyz;

    vec3 vertices[8] = vec3[8](
        vec3(min.x, min.y, min.z),
        vec3(max.x, min.y, min.z),
        vec3(max.x, max.y, min.z),
        vec3(min.x, max.y, min.z),
        vec3(min.x, min.y, max.z),
        vec3(max.x, min.y, max.z),
        vec3(max.x, max.y, max.z),
        vec3(min.x, max.y, max.z)
    );

   int indices[16] = int[16](
        0, 1, 2, 3, 0, 4, 5, 1, 2, 6, 5, 4, 7, 3, 6, 7
    );

    for (int i = 0; i < 16; ++i) {
        gl_Position = u_projection_matrix * u_view_matrix * modelMatrix * vec4(vertices[indices[i]], 1.0);
        EmitVertex();
    }

    EndPrimitive();

}  