#include "st_triangle.h"
#include "st_shader.h"


ST::Triangle::Triangle() {
	init();
	
	m_transform = glm::mat4(1);
	Move({ 0.0f,0.0f,0.0f });
	Scale({ 1.0f,1.0f,1.0f });
}

ST::Triangle::Triangle(glm::vec3 pos, glm::vec3 scale){
	init();

	m_transform = glm::mat4(1);
	Move(pos);
	Scale(scale);
}

void ST::Triangle::init() {
	ST::Shader vShader(ST::E_VERTEX_SHADER);
	vShader.loadSource(ST::basic_vShader_text);

	ST::Shader fShader(ST::E_FRAGMENT_SHADER);
	fShader.loadSource(ST::basic_fShader_text);

	program.attach(vShader);
	program.attach(fShader);
	program.link();

	// Geometry
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
	

	/*float vertex[] = {0.5f, 1.0f,0.0f,
					   1.0f,-1.0f,0.0f,
					  -1.0f,-1.0f,0.0f,

					   0.0f, 0.0f, 1.0f,
					   0.0f, 0.0f, 1.0f,
					   0.0f, 0.0f, 1.0f,
	};

	unsigned short indices[] = { 2,1,0 };

	b_vertex.bind(ST::Buffer::E_TARGET_VERTEX);

	b_vertex.init(sizeof(vertex));
	b_vertex.uploadData((void*)vertex, sizeof(vertex));

	b_indices.bind(ST::Buffer::E_TARGET_ELEMENTS);

	b_indices.init(sizeof(indices));
	b_indices.uploadData((void*)indices, sizeof(indices));*/

	if (glGetError() != GL_NO_ERROR) { printf("Error OpenGL\n"); }
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
	return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
}

glm::vec3 ST::Triangle::getScale(){
	//return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
	return glm::vec3();
}

glm::vec3 ST::Triangle::getRotation(){
	//return glm::vec3(m_transform[3][0], m_transform[3][1], m_transform[3][2]);
	return glm::vec3();
}

void ST::Triangle::Draw(){
	program.use();
	glBindVertexArray(mesh);
	//b_vertex.bind(ST::Buffer::E_TARGET_VERTEX);
	/*
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 18 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 18 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/
	GLuint uniform = 0;
	glGetUniformLocation(uniform, "u_m_trans");
	glUniformMatrix4fv(uniform, 1, GL_FALSE, &m_transform[0][0]);
	
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
}

ST::Triangle::~Triangle(){

}
