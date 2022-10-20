#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>

namespace ST {

	/*struct VertexInfo {
		float x, y, z; // Position
		//float nx, ny, nz; // Normals
		float r, g, b; // Color
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
		//void setRobolutions(int v);
		~Circle();
	//private:
		//void reload();
	};
}

#endif