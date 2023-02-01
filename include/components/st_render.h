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

		/* Assigns the mesh reference.
		If we pass null to it, it will no longer have a mesh. */
		void setMesh(ST::Mesh *m);

		/* Set the unique material. Basic already has one. */
		void setMaterial(std::unique_ptr<ST::Material>& m);

		std::unique_ptr<ST::Material> material;
		ST::Mesh* mesh = nullptr;

		RenderComponent(const RenderComponent& o);

		~RenderComponent();

		RenderComponent(RenderComponent&&) = default;
		RenderComponent& operator=(RenderComponent&&) = default;
	};
}

#endif