#version 330
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];
  
uniform mat4 u_projection_matrix;
uniform vec3 minColliderPos;
uniform vec3 maxColliderPos;

void GenerateLine(vec3 pos1, vec3 pos2){
    gl_Position = vec4(pos1,0.0);
    EmitVertex();
    gl_Position = vec4(pos2,0.0);
    EmitVertex();
    EndPrimitive();
}

void main(){
    GenerateLine(vec3(maxColliderPos.x,maxColliderPos.y,maxColliderPos.z),
                vec3(minColliderPos.x,minColliderPos.y,minColliderPos.z));

    GenerateLine(vec3(minColliderPos.x,maxColliderPos.y,maxColliderPos.z),
                vec3(minColliderPos.x,maxColliderPos.y,minColliderPos.z));

   GenerateLine(vec3(minColliderPos.x,maxColliderPos.y,minColliderPos.z),
                vec3(maxColliderPos.x,maxColliderPos.y,minColliderPos.z));

   GenerateLine(vec3(maxColliderPos.x,maxColliderPos.y,maxColliderPos.z),
                vec3(maxColliderPos.x,maxColliderPos.y,minColliderPos.z));
}  