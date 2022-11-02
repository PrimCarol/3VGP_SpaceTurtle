#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>
#include <st_components.h>

namespace ST {

	// --------------------------- Struct Comps ID ----------------------------
	enum CompType{
		kComp_None,
		kComp_Trans,
		kComp_Mesh,
		kComp_Material,
	};

	struct ComponentId {
		size_t value = 0;
		CompType type = ST::kComp_None;
	};

	struct TransformComponentId : ComponentId {	};
	struct MeshComponentId : ComponentId {};
	struct MaterialComponentId : ComponentId {};

	// --------------------------- Manager ----------------------------
	class GameObj_Manager{
	public:

		GameObj_Manager();

		//template<typename... Component>
		//GameObj& createGameObj(Component... comp);

		ComponentId createTransformComponent();
		ComponentId createMeshComponent();
		ComponentId createMaterialComponent();

		bool createGameObj(std::vector<ComponentId> c);

		TransformComponent* getTransformComponent(size_t id);
		MeshComponent* getMeshComponent(size_t id);
		MaterialComponent* getMaterialComponent(size_t id);

		//GameObj& root();

		~GameObj_Manager();
	private:
		size_t TransCompIndex_;
		size_t MeshCompIndex_;
		size_t MatCompIndex_;
		
		std::vector<TransformComponent> transformComponentList_;
		std::vector<MeshComponent> meshComponentList_;
		std::vector<MaterialComponent> materialComponentList_;

		GameObj_Manager(const GameObj_Manager& o);
	};
}

#endif