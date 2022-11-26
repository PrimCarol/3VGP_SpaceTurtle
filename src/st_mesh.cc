#include <st_mesh.h>
#include <math.h>
#include <cstdio>
#include <string>

ST::Mesh::Mesh(){
	gladLoadGL();
	internalId = 0;
	meshType_ = kMeshType_None;
}

GLuint ST::Mesh::getId(){
	return internalId;
}

ST::Mesh::~Mesh(){}

ST::Mesh::Mesh(const Mesh& o){
	internalId = o.internalId;
	meshType_ = o.meshType_;
}

void ST::Mesh::render(){}


// ----------------- Triangle ------------------
ST::Triangle::Triangle() : Mesh() {
	
	//struct VertexInfo {
	//	float x, y, z;
	//	float nx, ny, nz;
	//	float u, v;
	//};

	meshType_ = kMeshType_Triangle;

	/*VertexInfo vertices[] = {
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
	*/
}

void ST::Triangle::render(){
	glBindVertexArray(internalId);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
}

ST::Triangle::~Triangle() {}

// ----------------- Quad ------------------
ST::Quad::Quad() : Mesh() {

	//struct VertexInfo {
	//	float x, y, z;
	//	float nx, ny, nz;
	//	float u, v;-
	//};

	meshType_ = kMeshType_Quad;

	/*VertexInfo vertices[] = {
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
	*/
}

void ST::Quad::render() {
	glBindVertexArray(internalId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

ST::Quad::~Quad() {}

// ----------------- Circle ------------------
ST::Circle::Circle() : Mesh() {
	//struct VertexInfo {
	//	float x, y, z;
	//	float nx, ny, nz;
	//	float u, v;
	//};

	meshType_ = kMeshType_Circle;

	const int rebolutions = 10 + 1;

	VertexInfo vertices[rebolutions];

	float angle = (3.1415926535f * 2.0f) / (rebolutions-1);

	for (int i = 0; i < rebolutions - 1; i++) {
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
		vertices[i].u =  (1.0f - vertices[i].x) * 0.5f;
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

	meshType_ = kMeshType_Cube;

	VertexInfo vertices[] = {
		{{ 0.5f, 0.5f, -0.5f },	   {0.0f, 0.0f, 1.0f},     {0.0f, 0.0f}},
		{{ 0.5f,-0.5f, -0.5f },	   {0.0f, 0.0f, 1.0f},     {0.0f, 1.0f}},	//Front
		{{-0.5f,-0.5f, -0.5f },	   {0.0f, 0.0f, 1.0f},     {1.0f, 1.0f}},
		{{-0.5f, 0.5f, -0.5f },    {0.0f, 0.0f, 1.0f},     {1.0f, 0.0f}},

		{{-0.5f,  0.5f, -0.5f},    {1.0f, 0.0f, 0.0f},     {0.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f},    {1.0f, 0.0f, 0.0f},     {0.0f, 1.0f}},	//Right
		{{-0.5f, -0.5f,  0.5f},    {1.0f, 0.0f, 0.0f},     {1.0f, 1.0f}},
		{{-0.5f,  0.5f,  0.5f},    {1.0f, 0.0f, 0.0f},     {1.0f, 0.0f}},

		{{0.5f,  0.5f,  0.5f},	  {-1.0f, 0.0f, 0.0f},     {0.0f, 0.0f}},
		{{0.5f, -0.5f,  0.5f},    {-1.0f, 0.0f, 0.0f},     {0.0f, 1.0f}},	//Left
		{{0.5f, -0.5f, -0.5f},	  {-1.0f, 0.0f, 0.0f},     {1.0f, 1.0f}},
		{{0.5f,  0.5f, -0.5f},    {-1.0f, 0.0f, 0.0f},     {1.0f, 0.0f}},

		{{-0.5f,  0.5f,  0.5f},	  {0.0f, 0.0f,-1.0f},     {0.0f, 0.0f}},
		{{-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f,-1.0f},     {0.0f, 1.0f}},	//Back
		{{ 0.5f, -0.5f,  0.5f},	  {0.0f, 0.0f,-1.0f},     {1.0f, 1.0f}},
		{{ 0.5f,  0.5f,  0.5f},   {0.0f, 0.0f,-1.0f},     {1.0f, 0.0f}},

		{{ 0.5f, -0.5f, -0.5f},	   {0.0f,-1.0f, 0.0f},     {0.0f, 0.0f}},
		{{ 0.5f, -0.5f,  0.5f},    {0.0f,-1.0f, 0.0f},     {0.0f, 1.0f}},	//Bottom
		{{-0.5f, -0.5f,  0.5f},	   {0.0f,-1.0f, 0.0f},     {1.0f, 1.0f}},
		{{-0.5f, -0.5f, -0.5f},    {0.0f,-1.0f, 0.0f},     {1.0f, 0.0f}},

		{{-0.5f,  0.5f, -0.5f},	   {0.0f, 1.0f, 0.0f},     {1.0f, 1.0f}},
		{{-0.5f,  0.5f,  0.5f},    {0.0f, 1.0f, 0.0f},     {1.0f, 0.0f}},	//Top
		{{ 0.5f,  0.5f,  0.5f},	   {0.0f, 1.0f, 0.0f},     {0.0f, 0.0f}},
		{{ 0.5f,  0.5f, -0.5f},    {0.0f, 1.0f, 0.0f},     {0.0f, 1.0f}}
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

/*bool ST::Geometry::loadFromFile(const char* path) {
	printf("Loading OBJ file %s...\n", path);

	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		VertexInfo tempVertices;
		
		// Position
		tempVertices.x = vertex.x;
		tempVertices.y = vertex.y;
		tempVertices.z = vertex.z;

		//Normales
		tempVertices.nx = normal.x;
		tempVertices.ny = normal.y;
		tempVertices.nz = normal.z;

		// UV's
		tempVertices.u = uv.x;
		tempVertices.v = uv.y;

		vertices_.push_back(tempVertices);
		indices_.push_back(vertexIndex);
	}
	fclose(file);

	//VertexInfo* allVertices = &vertices_[0];
	//unsigned int* allIndices = &indices_[0];

	glGenVertexArrays(1, &internalId);
	glBindVertexArray(internalId);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(VertexInfo), &vertices_.front(), GL_STATIC_DRAW);
	//int sizeV = sizeof(*allVertices);
	//int sizeI = sizeof(*allIndices);
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



	return true;
}*/

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
		printf("Error on load file mesh: %s [%s] \n", warning, error);
		return false;
	}

	std::vector<VertexInfo> vertices;
	std::vector<uint32_t> indices;
	std::unordered_map<VertexInfo, uint32_t> uniqueVertices;


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

	return true;
}

void ST::Geometry::render(){
	glBindVertexArray(internalId);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, (void*)0);
}

ST::Geometry::~Geometry(){}
