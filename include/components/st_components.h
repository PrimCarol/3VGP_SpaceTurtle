#ifndef _SPACE_TURTLE_COMPONENTS_H_
#define _SPACE_TURTLE_COMPONENTS_H_ 1

#include <stdio.h>

namespace ST {

	// --------------------------- Struct Comps ID ----------------------------
	enum CompType {
		kComp_None,
		kComp_Trans,
		kComp_Render,
		kComp_Collider,
	};

	struct ComponentId {
		size_t value = -1;
		CompType type = ST::kComp_None;
	};

	struct TransformComponentId : ComponentId {};
	struct RenderComponentId : ComponentId {};
	struct ColliderComponentId : ComponentId {};

	// --------------------------- Usability ----------------------------

	class Components{
	public:
		Components();
		~Components();
	private:
		//Components(const Components& o);
	};
}

#endif