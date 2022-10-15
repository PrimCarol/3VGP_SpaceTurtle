#ifndef _SPACE_TURTLE_DRAWOBJ_H_
#define _SPACE_TURTLE_DRAWOBJ_H_ 1

#include <st_node.h>

#include <st_program.h>
#include <st_mesh.h>

namespace ST {

	class DrawObj : public Node{
	public:
		DrawObj();

		void draw();
		void setMesh(ST::Mesh *m);
		void setMaterial(ST::Program *p);

		~DrawObj();

	private:
		DrawObj(const DrawObj& o);

		ST::Program* program;
		ST::Mesh* mesh;
	};
}

#endif