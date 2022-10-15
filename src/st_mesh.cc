#include "st_mesh.h"

ST::Mesh::Mesh(){
	internalId = 0;
}

GLuint ST::Mesh::getId(){
	return internalId;
}

ST::Mesh::~Mesh(){}

ST::Mesh::Mesh(const Mesh& o){
	internalId = o.internalId;
}

void ST::Mesh::render(){

}


// ----------------- Triangle ------------------
ST::Triangle::Triangle() {
	struct VertexInfo {
		float x, y, z;
		float r, g, b;
	};

	VertexInfo vertices[] = {
		{ 0.0f, 0.5f,0.0f  ,  1.0f,0.0f,0.0f},
		{ 0.5f,-0.5f,0.0f  ,  0.0f,1.0f,0.0f},
		{-0.5f,-0.5f,0.0f  ,  0.0f,0.0f,1.0f},
	};

	unsigned int indices[] = { 0,1,2 };

	glGenVertexArrays(1, &internalId);
	glBindVertexArray(internalId);

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

void ST::Triangle::render(){
	//if (internalId) {
		glBindVertexArray(internalId);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
	//}
}

ST::Triangle::~Triangle() {

}

// ----------------- Quad ------------------
ST::Quad::Quad() {
	struct VertexInfo {
		float x, y, z;
		float r, g, b;
	};

	VertexInfo vertices[] = {
		{ 0.5f, 0.5f,0.0f  ,  1.0f,0.0f,0.0f},
		{ 0.5f,-0.5f,0.0f  ,  0.0f,1.0f,0.0f},
		{-0.5f,-0.5f,0.0f  ,  0.0f,0.0f,1.0f},
		{-0.5f, 0.5f,0.0f  ,  1.0f,1.0f,1.0f}
	};

	unsigned int indices[] = { 0,1,2  ,  0,2,3 };

	glGenVertexArrays(1, &internalId);
	glBindVertexArray(internalId);

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

void ST::Quad::render() {
	//if (internalId) {
	glBindVertexArray(internalId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	//}
}

ST::Quad::~Quad() {

}

