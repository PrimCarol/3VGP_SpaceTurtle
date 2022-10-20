#include <st_mesh.h>
#include <math.h>

ST::Mesh::Mesh(){
	gladLoadGL();
	internalId = 0;
}

GLuint ST::Mesh::getId(){
	return internalId;
}

ST::Mesh::~Mesh(){}

ST::Mesh::Mesh(const Mesh& o){
	internalId = o.internalId;
}

void ST::Mesh::render(){}


// ----------------- Triangle ------------------
ST::Triangle::Triangle() : Mesh() {
	
	struct VertexInfo {
		float x, y, z;
	};

	VertexInfo vertices[] = {
		 0.0f, 0.5f,0.0f,
		 0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f
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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	//glEnableVertexAttribArray(1);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}

void ST::Triangle::render(){
	glBindVertexArray(internalId);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
}

ST::Triangle::~Triangle() {}

// ----------------- Quad ------------------
ST::Quad::Quad() : Mesh() {
	struct VertexInfo {
		float x, y, z;
	};

	VertexInfo vertices[] = {
		 0.5f, 0.5f,0.0f,
		 0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		-0.5f, 0.5f,0.0f
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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	//glEnableVertexAttribArray(1);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

}

void ST::Quad::render() {
	glBindVertexArray(internalId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

ST::Quad::~Quad() {}

// ----------------- Circle ------------------
ST::Circle::Circle() : Mesh() {
	struct VertexInfo {
		float x, y, z;
	};

	const int rebolutions = 10 + 1;

	VertexInfo vertices[rebolutions];

	float angle = (3.1415926535f * 2.0f) / rebolutions;

	vertices[0].x = 0.5f;
	vertices[0].y = 0.0f;
	vertices[0].z = 0.0f;

	for (int i = 1; i < rebolutions; i++) {
		vertices[i].x = (float)cos(angle * i) * 0.5f;
		vertices[i].y = (float)sin(angle * i) * 0.5f;
		vertices[i].z = 0.0f;
	}

	unsigned int indices[rebolutions * 3];

	int contadorIndice = 0;
	for (int i = 0; i < rebolutions*3; i+=3){
		indices[i] = contadorIndice +1;
		indices[i+1] = contadorIndice +2;
		indices[i+2] = 0;
		contadorIndice++;
	}

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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	//glEnableVertexAttribArray(1);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

}

void ST::Circle::render() {
	glBindVertexArray(internalId);
	glDrawElements(GL_TRIANGLES, 10*3, GL_UNSIGNED_INT, (void*)0);
}

ST::Circle::~Circle() {}