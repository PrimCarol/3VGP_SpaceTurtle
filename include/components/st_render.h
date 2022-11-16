#ifndef _SPACE_TURTLE_RENDER_H_
#define _SPACE_TURTLE_RENDER_H_ 1

#include <components/st_components.h>

#include <st_mesh.h>
#include <st_material.h>

namespace ST {

	class RenderComponent : public Components {
	public:
		RenderComponent();

		void setMesh(ST::Mesh *m);
		void setMaterial(ST::Material* m);

		~RenderComponent();

		ST::Material* material;
		ST::Mesh* mesh;
		//RenderComponent(const RenderComponent& o);
	};
}

#endif