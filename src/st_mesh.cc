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

bool ST::Mesh::operator==(const Mesh& rhs){
	return internalId == rhs.internalId;
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

	vertices_.push_back({ {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.5f, 0.0f} });
	vertices_.push_back({ {1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} });

	indices_.push_back(0);
	indices_.push_back(1);
	indices_.push_back(2);

	glGenVertexArrays(1, &internalId);
	glBindVertexArray(internalId);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(VertexInfo), &vertices_.front(), GL_STATIC_DRAW);

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)indices_.size() * sizeof(unsigned int), &indices_.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ST::Triangle::render(){
	glBindVertexArray(internalId);

	SetCullMode(cullmode_);

	glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, (void*)0);
}

ST::Triangle::~Triangle() {
	glDeleteVertexArrays(1, &internalId);
	vertices_.clear();
	indices_.clear();
}

// ----------------- Quad ------------------
ST::Quad::Quad() : Mesh() {

	setName("Quad");

	vertices_.push_back({ {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ {1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} });

	indices_.push_back(0);
	indices_.push_back(1);
	indices_.push_back(2);
	indices_.push_back(0);
	indices_.push_back(2);
	indices_.push_back(3);

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)indices_.size() * sizeof(unsigned int), &indices_.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ST::Quad::render() {
	glBindVertexArray(internalId);
	
	SetCullMode(cullmode_);

	glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, (void*)0);
}

ST::Quad::~Quad() {
	glDeleteVertexArrays(1, &internalId);
	vertices_.clear();
	indices_.clear();
}

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

ST::Circle::~Circle() {
	glDeleteVertexArrays(1, &internalId);
	vertices_.clear();
	indices_.clear();
}

// ------------------- Cube -------------------
ST::Cube::Cube() : Mesh() {

	setName("Cube");

	//Front
	vertices_.push_back({ { 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} });
	
	indices_.push_back(0);indices_.push_back(1);indices_.push_back(2);
	indices_.push_back(0);indices_.push_back(2);indices_.push_back(3);
	
	//Right
	vertices_.push_back({ {-1.0f,  1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ {-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, -1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ {-1.0f,  1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });
	
	indices_.push_back(4); indices_.push_back(5); indices_.push_back(6);
	indices_.push_back(4); indices_.push_back(6); indices_.push_back(7);

	//Left
	vertices_.push_back({ { 1.0f,  1.0f,  1.0f}, { 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ { 1.0f, -1.0f,  1.0f}, { 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ { 1.0f, -1.0f, -1.0f}, { 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ { 1.0f,  1.0f, -1.0f}, { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} });

	indices_.push_back(8); indices_.push_back(9); indices_.push_back(10);
	indices_.push_back(8); indices_.push_back(10); indices_.push_back(11);

	//Back
	vertices_.push_back({ {-1.0f,  1.0f,  1.0f}, { 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ {-1.0f, -1.0f,  1.0f}, { 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ { 1.0f, -1.0f,  1.0f}, { 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ { 1.0f,  1.0f,  1.0f}, { 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} });

	indices_.push_back(12); indices_.push_back(13); indices_.push_back(14);
	indices_.push_back(12); indices_.push_back(14); indices_.push_back(15);

	//Bottom
	vertices_.push_back({ { 1.0f, -1.0f, -1.0f}, { 0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ { 1.0f, -1.0f,  1.0f}, { 0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, -1.0f,  1.0f}, { 0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, -1.0f, -1.0f}, { 0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} });

	indices_.push_back(16); indices_.push_back(17); indices_.push_back(18);
	indices_.push_back(16); indices_.push_back(18); indices_.push_back(19);

	//Top
	vertices_.push_back({ {-1.0f,  1.0f, -1.0f}, { 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ {-1.0f,  1.0f,  1.0f}, { 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ { 1.0f,  1.0f,  1.0f}, { 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ { 1.0f,  1.0f, -1.0f}, { 0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} });

	indices_.push_back(20); indices_.push_back(21); indices_.push_back(22);
	indices_.push_back(20); indices_.push_back(22); indices_.push_back(23);

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
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
}

void ST::Cube::render() {
	glBindVertexArray(internalId);
	
	SetCullMode(cullmode_);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, (void*)0);
}

ST::Cube::~Cube() {
	glDeleteVertexArrays(1, &internalId);
	vertices_.clear();
	indices_.clear();
}

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

ST::Geometry::~Geometry() {
	glDeleteVertexArrays(1, &internalId);
	vertices_.clear();
	indices_.clear();
}

ST::Test::Test()
{
}

ST::Test::Test(int howMany, std::vector<glm::mat4>* matrices){
	instancing = howMany;

	setName("Test");

	vertices_.push_back({ {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} });
	vertices_.push_back({ {1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} });
	vertices_.push_back({ {-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} });

	indices_.push_back(0);
	indices_.push_back(1);
	indices_.push_back(2);
	indices_.push_back(0);
	indices_.push_back(2);
	indices_.push_back(3);

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


	// Instancing ------
	GLuint instancingID = 0;
	glGenBuffers(1, &instancingID);
	glBindBuffer(GL_ARRAY_BUFFER, instancingID);
	glBufferData(GL_ARRAY_BUFFER, matrices->size() * sizeof(glm::mat4), matrices->data(), GL_STATIC_DRAW);
	if (howMany != 1) {
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
	}
	// Instancing ------


	// Indices
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)indices_.size() * sizeof(unsigned int), &indices_.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void ST::Test::render(){
	glBindVertexArray(internalId);
	if (instancing > 1) {
		glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, 0, instancing);
	}
}

ST::Test::~Test(){
	glDeleteVertexArrays(1, &internalId);
	vertices_.clear();
	indices_.clear();
}
