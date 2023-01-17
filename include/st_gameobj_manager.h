#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>
#include <components/st_transform.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_hierarchy.h>

#include <st_camera.h>

#include <memory>

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
		std::unique_ptr<ST::GameObj> createGameObj();
		const int getGameObjNum();

		void UpdateTransforms();
		//void UpdateRender();

		//ST::GameObj* tryPickObj();

		//GameObj& root();

		
		//std::vector<BeltComponent> beltComponentList_; 
		//std::vector<BeltRenderPairComponent> beltRenderPairComponentList_;  // Id trans y render
		//struct BeltRender {
		//	size_t belt_id;
		//	size_t render_id;
		//};
		
		//std::vector<std::optional<RenderComponent>> renderComponentList_;
		std::vector<GameObj*> GameObjsList_;
		std::vector<TransformComponent> transformComponentList_;
		std::vector<RenderComponent> renderComponentList_;
		std::vector<ColliderComponent> colliderComponentList_;
		std::vector<HierarchyComponent> hierarchyComponentList_;

		std::unique_ptr<ST::Camera> cam_;
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