#include "st_triangle.h"

ST::Triangle::Triangle(){
	
	GLchar* vertexText =
		"#version 330\n"
		"layout (location=0) in vec3 a_position;\n"
		"layout (location=1) in vec3 a_color;\n"
		"out vec3 color;\n"
		"void main() {\n"
		"color = a_color;\n"
		"gl_Position = vec4(a_position, 1.0);\n"
		"}\n";
	GLchar* fragmentText =
		"#version 330\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"void main() {\n"
		"FragColor = vec4(color, 1.0);\n"
		"}\n";

	GLuint vshader = -1;
	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vertexText, 0);
	glCompileShader(vshader);

	GLuint fshader = -1;
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragmentText, 0);
	glCompileShader(fshader);

	program = glCreateProgram();
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);

	VertexInfo vertices[] = {
		{ 0.0f, 0.5f,0.0f  ,  1.0f,0.0f,0.0f},
		{ 0.5f,-0.5f,0.0f  ,  0.0f,1.0f,0.0f},
		{-0.5f,-0.5f,0.0f  ,  0.0f,0.0f,1.0f},
	};

	unsigned int indices[] = { 0,1,2 };

	// Mesh
	glGenVertexArrays(1, &mesh);
	glBindVertexArray(mesh);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}

void ST::Triangle::Draw(){
	glUseProgram(program);
	glBindVertexArray(mesh);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

ST::Triangle::~Triangle(){

}
