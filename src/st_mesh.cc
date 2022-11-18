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
		float nx, ny, nz;
		float u, v;
	};

	VertexInfo vertices[] = {
		     /* Pos */          /* Normal */        /* UV */
		 0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f,     0.5f, 0.0f,
		 1.0f,-1.0f, 0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
		-1.0f,-1.0f, 0.0f,   0.0f, 0.0f, 1.0f,     1.0f, 1.0f
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
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// UV's
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

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
		float nx, ny, nz;
		float u, v;
	};

	VertexInfo vertices[] = {
			/*Pos*/ 		    /* Normal */        /* UV */
		 1.0f, 1.0f,0.0f,	 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
		 1.0f,-1.0f,0.0f,	 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
		-1.0f,-1.0f,0.0f,	 0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
		-1.0f, 1.0f,0.0f,    0.0f, 0.0f, 1.0f,     1.0f, 0.0f
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
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// UV's
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

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
		float nx, ny, nz;
		float u, v;
	};

	const int rebolutions = 10 + 1;

	VertexInfo vertices[rebolutions];

	float angle = (3.1415926535f * 2.0f) / (rebolutions-1);

	for (int i = 0; i < rebolutions-1; i++) {
		// Pos
		vertices[i].x = (float)cos(angle * i); //* 1.0f;
		vertices[i].y = (float)sin(angle * i); //* 1.0f;
		vertices[i].z = 0.0f;
		// Normals
		vertices[i].nx = 0.0f;
		vertices[i].ny = 0.0f;
		vertices[i].nz = 1.0f;
	}

	vertices[rebolutions - 1].nx = 0.0f;
	vertices[rebolutions - 1].ny = 0.0f;
	vertices[rebolutions - 1].nz = 1.0f;

	vertices[rebolutions-1].x = 0.0f;
	vertices[rebolutions-1].y = 0.0f;
	vertices[rebolutions-1].z = 0.0f;

	for (size_t i = 0; i < rebolutions; i++){
		// UV's
		vertices[i].u =  (1.0f + vertices[i].x) * 0.5f;
		vertices[i].v =  (1.0f - vertices[i].y) * 0.5f;
	}

	unsigned int indices[(rebolutions * 3)+3];

	int contadorIndice = -1;
	for (int i = 0; i < rebolutions*3; i+=3){
		indices[i] = contadorIndice +2;
		indices[i+1] = contadorIndice +1;
		indices[i+2] = rebolutions-1;
		contadorIndice++;
	}

	indices[(rebolutions*3)] = 0;
	indices[(rebolutions * 3) + 1] = contadorIndice - 1;
	indices[(rebolutions * 3) + 2] = rebolutions - 1;

	glGenVertexArrays(1, &internalId);
	glBindVertexArray(internalId);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
	glEnableVertexAttribArray(0);
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

}

void ST::Circle::render() {
	glBindVertexArray(internalId);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, (11*3)+3, GL_UNSIGNED_INT, (void*)0);
}

ST::Circle::~Circle() {}

// ------------------- Cube -------------------
ST::Cube::Cube() : Mesh() {
	struct VertexInfo {
		float x, y, z;
		float nx, ny, nz;
		float u, v;
	};

	VertexInfo vertices[] = {
		/*Pos*/ 		        /* Normal */         /* UV */
	  0.5f, 0.5f, -0.5f,	   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
	  0.5f,-0.5f, -0.5f,	   0.0f, 0.0f, 1.0f,     0.0f, 1.0f,	//Front
	 -0.5f,-0.5f, -0.5f,	   0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
	 -0.5f, 0.5f, -0.5f,       0.0f, 0.0f, 1.0f,     1.0f, 0.0f,

	 -0.5f,  0.5f, -0.5f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
	 -0.5f, -0.5f, -0.5f,      1.0f, 0.0f, 0.0f,     0.0f, 1.0f,	//Right
	 -0.5f, -0.5f,  0.5f,      1.0f, 0.0f, 0.0f,     1.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 0.0f,     1.0f, 0.0f,

	  0.5f,  0.5f,  0.5f,	  -1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
	  0.5f, -0.5f,  0.5f,     -1.0f, 0.0f, 0.0f,     0.0f, 1.0f,	//Left
	  0.5f, -0.5f, -0.5f,	  -1.0f, 0.0f, 0.0f,     1.0f, 1.0f,
	  0.5f,  0.5f, -0.5f,     -1.0f, 0.0f, 0.0f,     1.0f, 0.0f,

	 -0.5f,  0.5f,  0.5f,	   0.0f, 0.0f,-1.0f,     0.0f, 0.0f,
	 -0.5f, -0.5f,  0.5f,      0.0f, 0.0f,-1.0f,     0.0f, 1.0f,	//Back
	  0.5f, -0.5f,  0.5f,	   0.0f, 0.0f,-1.0f,     1.0f, 1.0f,
	  0.5f,  0.5f,  0.5f,      0.0f, 0.0f,-1.0f,     1.0f, 0.0f,

      0.5f, -0.5f, -0.5f,	   0.0f,-1.0f, 0.0f,     0.0f, 0.0f,
	  0.5f, -0.5f,  0.5f,      0.0f,-1.0f, 0.0f,     0.0f, 1.0f,	//Bottom
	 -0.5f, -0.5f,  0.5f,	   0.0f,-1.0f, 0.0f,     1.0f, 1.0f,
	 -0.5f, -0.5f, -0.5f,      0.0f,-1.0f, 0.0f,     1.0f, 0.0f,

	 -0.5f,  0.5f, -0.5f,	   0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f,      0.0f, 1.0f, 0.0f,     1.0f, 0.0f,	//Top
	  0.5f,  0.5f,  0.5f,	   0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
	  0.5f,  0.5f, -0.5f,      0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
	};

	unsigned int indices[] = { 0,1,2 , 0,2,3  ,  4,5,6 , 4,6,7,
							   8,9,10 , 8,10,11  ,  12,13,14 , 12,14,15,
							   16,17,18  ,  16,18,19  ,  20,21,22 , 20,22,23 };

	glGenVertexArrays(1, &internalId);
	glBindVertexArray(internalId);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
	glEnableVertexAttribArray(0);
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// UV's
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}

void ST::Cube::render() {
	glBindVertexArray(internalId);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}

ST::Cube::~Cube() {}

// ------------------- OBJ -------------------
ST::Geometry::Geometry() : Mesh() {

}

void ST::Geometry::loadFromFile(const char* path){

}

void ST::Geometry::render(){

}

ST::Geometry::~Geometry(){}
