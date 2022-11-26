#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>

// Testing
#include <vector>
#include <transform.hpp>

namespace ST {

	struct VertexInfo {
		glm::vec3 pos; // Position
		glm::vec3 normal; // Normals
		glm::vec2 uv; // UVs

		bool VertexInfo::operator==(const VertexInfo& other) const {
			return (pos == other.pos && normal == other.normal && uv == other.uv);
		}
	};

	enum MeshType{
		kMeshType_None,
		kMeshType_Triangle,
		kMeshType_Quad,
		kMeshType_Circle,
		kMeshType_Cube,
		kMeshType_Custom,
	};

	class Mesh{


	public:
		Mesh();
		GLuint getId();
		MeshType meshType_;
		virtual void render();
		~Mesh();
		Mesh(const Mesh& o);
	protected:
		GLuint internalId;
	};

	// ------------------- Basics 2D -------------------
	class Triangle : public Mesh{
	public:
		Triangle();
		void render() override;
		~Triangle();
	};

	class Quad : public Mesh {
	public:
		Quad();
		void render() override;
		~Quad();
	};

	class Circle : public Mesh {
	public:
		Circle();
		void render() override;
		~Circle();
	};

	// ------------------- 3D -------------------
	
	// ------- Cube -------
	class Cube : public Mesh {
	public:
		Cube();
		void render() override;
		~Cube();
	};

	// ------- Geometry -------
	class Geometry : public Mesh {
	public:
		Geometry();
	
		bool loadFromFile(const char* path);
		void render() override;
	
		~Geometry();

	private:
		std::vector<VertexInfo> vertices_;
		std::vector<unsigned int> indices_;
	};
}

#endif

#include "gtx/hash.hpp"
namespace std {

	template<>

	struct hash<ST::VertexInfo> {

		size_t operator() (const ST::VertexInfo& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec2>()(vertex.uv) << 1)) >> 1);
		}
	};
}

/*bool loadOBJ(const char* src, illo::illoGeometry& _geometry)
{
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning;
	std::string error;

	if (!tinyobj::LoadObj(
		&attributes,
		&shapes,
		&materials,
		&warning,
		&error,
		src))
	{
		throw std::runtime_error("ast::assets::loadOBJFile: Error: " + warning + error);
		return false;
	}

	std::vector<illo::Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<illo::Vertex> texVertices;
	std::vector<uint32_t> texIndices;
	std::unordered_map<illo::Vertex, uint32_t> uniqueVertices;

	// Loop through all the shapes that there found.
	for (const auto& shape : shapes)
	{
		// For each shape, loop through its indices.
		for (const auto& index : shape.mesh.indices)
		{
			// Construct a new (x, y, z) position for the current mesh index.
			glm::vec3 position{
				attributes.vertices[(int)3 * index.vertex_index + 0],
				attributes.vertices[(int)3 * index.vertex_index + 1],
				attributes.vertices[(int)3 * index.vertex_index + 2] };

			glm::vec3 normals{
				attributes.normals[(int)3 * index.normal_index + 0],
				attributes.normals[(int)3 * index.normal_index + 1],
				attributes.normals[(int)3 * index.normal_index + 2] };

			// Construct a new (u, v) texture coordinate for the current mesh index.
			glm::vec2 texCoord{
				attributes.texcoords[(int)2 * index.texcoord_index + 0],
				1.0f - attributes.texcoords[(int)2 * index.texcoord_index + 1] };

			// Construct a vertex with the extracted data.
			illo::Vertex vertex{ position, normals, texCoord };

			// This will help deduplicate vertices - we maintain a hash map where a
			// vertex is used as a unique key with its value being which index can
			// be used to locate the vertex. The vertex is only added if it has not
			// been added before.
			if (uniqueVertices.count(vertex) == 0)
			{
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}

			geometry.indices.push_back(uniqueVertices[vertex]);
		}
	}

	for (const auto& vertex : vertices)
	{
		// Position
		geometry.vertices.push_back(vertex.pos.x);
		geometry.vertices.push_back(vertex.pos.y);
		geometry.vertices.push_back(vertex.pos.z);

		geometry.vertices.push_back(vertex.normals.x);
		geometry.vertices.push_back(vertex.normals.y);
		geometry.vertices.push_back(vertex.normals.z);

		// Texture coordinate
		geometry.vertices.push_back(vertex.texCoords.x);
		geometry.vertices.push_back(vertex.texCoords.y);


	}

	return true;
}*/