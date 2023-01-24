#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>
#include <components/st_transform.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_hierarchy.h>

#include <memory>
#include <optional>

namespace ST {

	// --------------------------- Manager ----------------------------
	class GameObj_Manager{
	public:

		GameObj_Manager();
		~GameObj_Manager();
		
		ComponentId createTransformComponent();
		ComponentId createRenderComponent();
		ComponentId createColliderComponent();
		ComponentId createHierarchyComponent();

		//std::unique_ptr<ST::GameObj> createGameObj(const std::vector<ComponentId> c);
		// With all components (Hierarchy, Transform, Render)
		std::unique_ptr<ST::GameObj> createGameObj();
		
		//void markToDeletObj(int ID);
		const int getGameObjNum();
		
		//std::vector<std::optional<RenderComponent>> renderComponentList_;
		std::vector<GameObj*> GameObjsList_;
		std::vector<std::optional<TransformComponent>> transformComponentList_;
		std::vector<std::optional<RenderComponent>> renderComponentList_;
		std::vector<std::optional<ColliderComponent>> colliderComponentList_;
		std::vector<std::optional<HierarchyComponent>> hierarchyComponentList_;

	private:

		size_t TransCompIndex_;
		size_t RenderCompIndex_;
		size_t ColliderCompIndex_;
		size_t HierarchyCompIndex_;
		
		std::shared_ptr<ST::Program> basicProgram; // Default Shader Program to render.

		GameObj_Manager(const GameObj_Manager& o);
	};
}

#endif