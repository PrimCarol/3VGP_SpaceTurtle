#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D screenTexture;
vec2 screenSize;

const int blurRadius = 10;
const float blurAmount = 1.0 / float((blurRadius * 2 + 1) * (blurRadius * 2 + 1));

void main(){

    screenSize.x = 1028;
    screenSize.y = 1028;

    vec3 col = vec3(0.0);
    for(int i = -blurRadius; i <= blurRadius; ++i)
    {
        for(int j = -blurRadius; j <= blurRadius; ++j)
        {
            vec2 offset = vec2(float(i), float(j)) / screenSize;
            col += texture(screenTexture, TexCoords + offset).rgb;
        }
    }
    FragColor = vec4(col * blurAmount, 1.0);
}