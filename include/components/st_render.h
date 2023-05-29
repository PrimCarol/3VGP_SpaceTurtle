#ifndef _SPACE_TURTLE_RENDER_H_
#define _SPACE_TURTLE_RENDER_H_ 1

#include <st_mesh.h>
#include <st_material.h>
#include <memory>

namespace ST {

	class RenderComponent {
	public:
		RenderComponent();

		/**
		* @brief Assigns the mesh reference. If we pass null to it, it will no longer have a mesh.
		*/
		void setMesh(ST::Mesh *m);

		ST::Material material;
		ST::Mesh* mesh;

		CullMode thiscullmode_;
		DepthMode thisdepthmode_;

		bool visible_;
		bool castShadow_;

		~RenderComponent();
	};
}

#endif