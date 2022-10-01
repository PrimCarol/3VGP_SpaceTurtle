
#version 330
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_color;

//uniform float CustomData;

out vec3 color;

void main() {
	//float new_x = a_position.x*cos(CustomData) - a_position.y*sin(CustomData);
    //float new_y = a_position.y*cos(CustomData) + a_position.x*sin(CustomData);
    //gl_Position.x = new_x;
    //gl_Position.y = new_y;

	color = a_color;
	//color.x += CustomData;
	gl_Position = vec4(a_position, 1.0);	
}