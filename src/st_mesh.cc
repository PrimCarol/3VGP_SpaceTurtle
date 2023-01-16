#include <st_mesh.h>
#include <math.h>
#include <cstdio>
#include <string>

ST::Mesh::Mesh(){
	gladLoadGL();
	internalId = 0;

	name_ = nullptr;
	cullmode_ = ST::kCull_Back;
}

const GLuint ST::Mesh::getId(){
	return internalId;
}

const char* ST::Mesh::getName(){
	if (!name_) { return "No Name"; }
	return name_;
}

void ST::Mesh::setName(char* n){
	if (n) { name_ = n; }
}

ST::Mesh::~Mesh(){
	glDeleteVertexArrays(1, &internalId);
}

ST::Mesh::Mesh(const Mesh& o){
	name_ = o.name_;
	internalId = o.internalId;

	cullmode_ = o.cullmode_;
}

void ST::Mesh::render(){}

// ------ Extra Functions ------
void SetCullMode(ST::CullMode c) {

	switch (c){
	case ST::kCull_Disable:
		glDisable(GL_CULL_FACE);
		break;
	case ST::kCull_Front:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case ST::kCull_Back:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	case ST::kCull_Both:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;
	}
}


// ----------------- Triangle ------------------
ST::Triangle::Triangle() : Mesh() {
	
	setName("Triangle");

	VertexInfo vertices[] = {
		{{ 0.0f, 1.0f, 0.0f},   {0.0f, 0.0f, -1.0f},     {0.5f, 0.0f}},
		{{ 1.0f,-1.0f, 0.0f},   {0.0f, 0.0f, -1.0f},     {0.0f, 1.0f}},
		{{-1.0f,-1.0f, 0.0f},   {0.0f, 0.0f, -1.0f},     {1.0f, 1.0f}}
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// UV's
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ST::Triangle::render(){
	glBindVertexArray(internalId);

	SetCullMode(cullmode_);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
}

ST::Triangle::~Triangle() {}

// ----------------- Quad ------------------
ST::Quad::Quad() : Mesh() {

	setName("Quad");

	VertexInfo vertices[] = {
		{{ 1.0f, 1.0f,0.0f},  {0.0f, 0.0f, -1.0f},     {0.0f, 0.0f}},
		{{ 1.0f,-1.0f,0.0f},  {0.0f, 0.0f, -1.0f},     {0.0f, 1.0f}},
		{{-1.0f,-1.0f,0.0f},  {0.0f, 0.0f, -1.0f},     {1.0f, 1.0f}},
		{{-1.0f, 1.0f,0.0f},  {0.0f, 0.0f, -1.0f},     {1.0f, 0.0f}}
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// UV's
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ST::Quad::render() {
	glBindVertexArray(internalId);
	
	SetCullMode(cullmode_);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

ST::Quad::~Quad() {}

// ----------------- Circle ------------------
ST::Circle::Circle() : Mesh() {

	setName("Circle");

	const int rebolutions = 10 + 1;
	changeRebolutions(rebolutions);
}

void ST::Circle::render() {
	glBindVertexArray(internalId);

	SetCullMode(cullmode_);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size() * sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);
}

void ST::Circle::changeRebolutions(int r){
	if (r > 3 && rebolutions_ != r) {

		vertices_.clear();
		indices_.clear();

		rebolutions_ = r + 1;

		float angle = (3.1415926535f * 2.0f) / (rebolutions_ - 1);

		for (int i = 0; i < rebolutions_ - 1; i++) {
			VertexInfo vertices;
			// Pos
			vertices.pos.x = (float)cos(angle * i);
			vertices.pos.y = (float)sin(angle * i);
			vertices.pos.z = 0.0f;
			// Normals
			vertices.normal.x = 0.0f;
			vertices.normal.y = 0.0f;
			vertices.normal.z = -1.0f;

			vertices_.push_back(vertices);
		}

		VertexInfo verticesLast;
		verticesLast.normal.x = 0.0f;
		verticesLast.normal.y = 0.0f;
		verticesLast.normal.z = -1.0f;

		verticesLast.pos.x = 0.0f;
		verticesLast.pos.y = 0.0f;
		verticesLast.pos.z = 0.0f;

		vertices_.push_back(verticesLast);

		for (size_t i = 0; i < rebolutions_; i++) {
			// UV's
			vertices_[i].uv.x = (1.0f - vertices_[i].pos.x) * 0.5f;
			vertices_[i].uv.y = (1.0f - vertices_[i].pos.y) * 0.5f;
		}

		int contadorIndice = -1;
		for (int i = 0; i < rebolutions_ * 3; i += 3) {
			indices_.push_back(contadorIndice + 2);
			indices_.push_back(contadorIndice + 1);
			indices_.push_back(rebolutions_ - 1);
			contadorIndice++;
		}

		indices_.push_back(0);
		indices_.push_back(contadorIndice - 1);
		indices_.push_back(rebolutions_ - 1);

		glGenVertexArrays(1, &internalId);
		glBindVertexArray(internalId);

		GLuint gVBO = 0;
		glGenBuffers(1, &gVBO);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(VertexInfo), &vertices_.front(), GL_STATIC_DRAW);

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
		glEnableVertexAttribArray(0);
		// Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
		// UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
		glEnableVertexAttribArray(2);

		// Indices
		GLuint gEBO = 0;
		glGenBuffers(1, &gEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_.front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

int ST::Circle::getRebolutions(){
	return (rebolutions_ -1);
}

ST::Circle::~Circle() {}

// ------------------- Cube -------------------
ST::Cube::Cube() : Mesh() {

	setName("Cube");

	VertexInfo vertices[] = {
		{{ 1.0f, 1.0f, -1.0f },	   {0.0f, 0.0f, -1.0f},     {0.0f, 0.0f}},
		{{ 1.0f,-1.0f, -1.0f },	   {0.0f, 0.0f, -1.0f},     {0.0f, 1.0f}},	//Front
		{{-1.0f,-1.0f, -1.0f },	   {0.0f, 0.0f, -1.0f},     {1.0f, 1.0f}},
		{{-1.0f, 1.0f, -1.0f },    {0.0f, 0.0f, -1.0f},     {1.0f, 0.0f}},

		{{-1.0f,  1.0f, -1.0f},   {-1.0f, 0.0f, 0.0f},     {0.0f, 0.0f}},
		{{-1.0f, -1.0f, -1.0f},   {-1.0f, 0.0f, 0.0f},     {0.0f, 1.0f}},	//Right
		{{-1.0f, -1.0f,  1.0f},   {-1.0f, 0.0f, 0.0f},     {1.0f, 1.0f}},
		{{-1.0f,  1.0f,  1.0f},   {-1.0f, 0.0f, 0.0f},     {1.0f, 0.0f}},

		{{1.0f,  1.0f,  1.0f},	  { 1.0f, 0.0f, 0.0f},     {0.0f, 0.0f}},
		{{1.0f, -1.0f,  1.0f},    { 1.0f, 0.0f, 0.0f},     {0.0f, 1.0f}},	//Left
		{{1.0f, -1.0f, -1.0f},	  { 1.0f, 0.0f, 0.0f},     {1.0f, 1.0f}},
		{{1.0f,  1.0f, -1.0f},    { 1.0f, 0.0f, 0.0f},     {1.0f, 0.0f}},

		{{-1.0f,  1.0f,  1.0f},	  {0.0f, 0.0f, 1.0f},     {0.0f, 0.0f}},
		{{-1.0f, -1.0f,  1.0f},   {0.0f, 0.0f, 1.0f},     {0.0f, 1.0f}},	//Back
		{{ 1.0f, -1.0f,  1.0f},	  {0.0f, 0.0f, 1.0f},     {1.0f, 1.0f}},
		{{ 1.0f,  1.0f,  1.0f},   {0.0f, 0.0f, 1.0f},     {1.0f, 0.0f}},

		{{ 1.0f, -1.0f, -1.0f},	   {0.0f,-1.0f, 0.0f},     {0.0f, 0.0f}},
		{{ 1.0f, -1.0f,  1.0f},    {0.0f,-1.0f, 0.0f},     {0.0f, 1.0f}},	//Bottom
		{{-1.0f, -1.0f,  1.0f},	   {0.0f,-1.0f, 0.0f},     {1.0f, 1.0f}},
		{{-1.0f, -1.0f, -1.0f},    {0.0f,-1.0f, 0.0f},     {1.0f, 0.0f}},

		{{-1.0f,  1.0f, -1.0f},	   {0.0f, 1.0f, 0.0f},     {1.0f, 1.0f}},
		{{-1.0f,  1.0f,  1.0f},    {0.0f, 1.0f, 0.0f},     {1.0f, 0.0f}},	//Top
		{{ 1.0f,  1.0f,  1.0f},	   {0.0f, 1.0f, 0.0f},     {0.0f, 0.0f}},
		{{ 1.0f,  1.0f, -1.0f},    {0.0f, 1.0f, 0.0f},     {0.0f, 1.0f}}
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int), &indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ST::Cube::render() {
	glBindVertexArray(internalId);
	
	SetCullMode(cullmode_);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}

ST::Cube::~Cube() {}

// ------------------- OBJ -------------------
ST::Geometry::Geometry() : Mesh() {
	setName("Custom");
}

#include <tiny_obj_loader.h>
#include <unordered_map>

bool ST::Geometry::loadFromFile(const char* path) {
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;
	std::string warning;
	std::string error;

	if (!tinyobj::LoadObj(
		&attributes, &shapes, NULL, &warning, &error, path)){
		printf("Error on load file mesh: %s [%s] \n", warning.c_str(), error.c_str());
		return false;
	}

	std::vector<VertexInfo> vertices;
	std::vector<uint32_t> indices;
	std::unordered_map<VertexInfo, uint32_t> uniqueVertices;

	//char* name = new char[shapes[0].name.length() + 1];
	//strcpy(name, shapes[0].name.c_str());
	setName("Custom");

	for (const auto& shape : shapes){

		for (const auto& index : shape.mesh.indices){
			glm::vec3 position{
				attributes.vertices[(int)3 * index.vertex_index + 0],
				attributes.vertices[(int)3 * index.vertex_index + 1],
				attributes.vertices[(int)3 * index.vertex_index + 2] };

			glm::vec3 normals{
				attributes.normals[(int)3 * index.normal_index + 0],
				attributes.normals[(int)3 * index.normal_index + 1],
				attributes.normals[(int)3 * index.normal_index + 2] };

			glm::vec2 texCoord{
				attributes.texcoords[(int)2 * index.texcoord_index + 0],
				1.0f - attributes.texcoords[(int)2 * index.texcoord_index + 1] };

			VertexInfo vertex{ position, normals, texCoord };

			if (uniqueVertices.count(vertex) == 0)
			{
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}

			indices_.push_back(uniqueVertices[vertex]);
		}
	}

	for (const auto& vertex : vertices){
		VertexInfo tempVertices;

		// Position
		tempVertices.pos = vertex.pos;

		//Normales
		tempVertices.normal = vertex.normal;

		// UV's
		tempVertices.uv = vertex.uv;

		vertices_.push_back(tempVertices);
	}

	glGenVertexArrays(1, &internalId);
	glBindVertexArray(internalId);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(VertexInfo), &vertices_.front(), GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
	glEnableVertexAttribArray(0);
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// UV's
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

void ST::Geometry::render(){
	glBindVertexArray(internalId);
	
	SetCullMode(cullmode_);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, (void*)0);
}

ST::Geometry::~Geometry() {}
