#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
//uniform sampler2D gDepth;

uniform int visualMode;

void main(){ 

    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    //float Depth = texture(gDepth, TexCoords).r;

    if(visualMode == 0){
        FragColor = vec4(Diffuse,1.0);
    }else if(visualMode == 1){
        FragColor = vec4(FragPos,1.0);
    }else if(visualMode == 2){
        FragColor = vec4(Normal,1.0);
    }
}