#ifndef _SPACE_TURTLE_RENDER_H_
#define _SPACE_TURTLE_RENDER_H_ 1

#include <components/st_components.h>

#include <st_mesh.h>
#include <st_material.h>
#include <memory>

namespace ST {

	class RenderComponent : public Components {
	public:
		RenderComponent();

		void setMesh(ST::Mesh *m);
		void setMaterial(std::unique_ptr<ST::Material>& m);

		~RenderComponent();

		RenderComponent(RenderComponent&&) = default;
		RenderComponent& operator=(RenderComponent&&) = default;

		std::unique_ptr<ST::Material> material;
		ST::Mesh* mesh = nullptr;
		//RenderComponent(const RenderComponent& o);
	};
}

#endif