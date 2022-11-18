#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>

namespace ST {

	/*struct VertexInfo {
		float x, y, z; // Position
		//float nx, ny, nz; // Normals
		//float u, v; // UVs
	};*/

	class Mesh{
	public:
		Mesh();
		GLuint getId();
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

		void loadFromFile(const char* path);
		void render() override;

		~Geometry();
	private:
		//unsigned int indices;
	};
}

#endif