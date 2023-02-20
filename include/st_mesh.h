#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>
#include <vector>
#include <transform.hpp>

namespace ST {

	struct VertexInfo {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;

		bool VertexInfo::operator==(const VertexInfo& other) const {
			return (pos == other.pos && normal == other.normal && uv == other.uv);
		}
	};

	struct InstanceInfo {
		glm::mat4 matrix;
		glm::vec4 color;
	};

	enum CullMode{
		kCull_Disable,
		kCull_Front,
		kCull_Back,
		kCull_Both
	};

	// ------------------- BASE -------------------
	class Mesh{

	public:
		Mesh();
		const GLuint getId();

		const char* getName();
		void setName(char* n);

		virtual void render();

		std::vector<VertexInfo> vertices_;
		std::vector<unsigned int> indices_;

		bool operator==(const Mesh& rhs);

		~Mesh();
		Mesh(const Mesh& o);
	protected:
		const char* name_;
		GLuint internalId;

		CullMode cullmode_;
	};

	// ------------------- Test -------------------
	class Test : public Mesh {
	public:
		Test();
		Test(std::vector<glm::mat4>* matrices);
		void render() override;
		int instancing = 1;
		~Test();
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
		void changeRebolutions(int r);
		int getRebolutions();
		~Circle();
	private:
		int rebolutions_;
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
	};
}

#endif

// ---- Geometry optimization ----
#include "gtx/hash.hpp"
namespace std {

	template<>
	struct hash<ST::VertexInfo> {
		size_t operator() (const ST::VertexInfo& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec2>()(vertex.uv) << 1)) >> 1);
		}
	};
}