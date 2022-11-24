#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>

// Testing
#include <vector>
#include <transform.hpp>

namespace ST {

	struct VertexInfo {
		float x, y, z; // Position
		float nx, ny, nz; // Normals
		float u, v; // UVs
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
		std::vector<glm::vec3> vertices_;
		std::vector<glm::vec2> uvs_;
		std::vector<glm::vec3> normals_;
	};
}

#endif