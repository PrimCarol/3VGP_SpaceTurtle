#ifndef _SPACE_TURTLE_MESH_H_
#define _SPACE_TURTLE_MESH_H_ 1

#include <glad.h>

namespace ST {

	class Mesh{
	public:
		Mesh();


		~Mesh();
	private:

		Mesh(const Mesh& o);
	};
}

#endif