#include "st_triangle.h"

ST::Triangle::Triangle() {
	init();
	
	m_transform = glm::mat4(1);
	Move({ 0.0f,0.0f,0.0f });
	Scale({ 0.5f,0.5f,1.0f });
}

ST::Triangle::Triangle(glm::vec3 pos, glm::vec3 scale){
	init();

	Move(pos);
	Scale(scale);
}

void ST::Triangle::init() {
	gladLoadGL();

	GLchar* vertexText =
		"#version 330\n"
		"layout (location=0) in vec3 a_position;\n"
		"layout (location=1) in vec3 a_color;\n"
		"uniform mat4 u_m_trans;\n"
		"uniform mat4 u_m_view;\n"
		"out vec3 color;\n"
		"void main() {\n"
		"color = a_color;\n"
		//"gl_Position = vec4(a_position, 1.0);\n"
		//"gl_Position = u_m_view * u_m_trans * vec4(a_position, 1);\n"
		"gl_Position = u_m_trans * vec4(a_position, 1);\n"
		"}\n";
	GLchar* fragmentText =
		"#version 330\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"void main() {\n"
		"FragColor = vec4(color, 1.0);\n"
		"}\n";

	GLuint vshader = 0;
	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vertexText, 0);
	glCompileShader(vshader);

	GLuint fshader = 0;
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

void ST::Triangle::Move(glm::vec3 newPos){
	m_transform = glm::translate(m_transform, newPos);
}

void ST::Triangle::Scale(glm::vec3 newScale){
	m_transform = glm::scale(m_transform, newScale);
}

void ST::Triangle::RotateX(float r){
	m_transform = glm::rotate(m_transform, r, {1.0f,0.0f,0.0f});
}
void ST::Triangle::RotateY(float r) {
	m_transform = glm::rotate(m_transform, r, { 0.0f,1.0f,0.0f });
}
void ST::Triangle::RotateZ(float r) {
	m_transform = glm::rotate(m_transform, r, { 0.0f,0.0f,1.0f });
}

glm::vec3 ST::Triangle::getPosition(){	
	//return glm::vec3(m_transform[0][3], m_transform[1][3], m_transform[2][3]);
	return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
}

void ST::Triangle::Draw(){
	glUseProgram(program);
	glBindVertexArray(mesh);

	GLuint uniform = 0;
	glGetUniformLocation(uniform, "u_m_trans");
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &m_transform[0][0]);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

ST::Triangle::~Triangle(){

}
