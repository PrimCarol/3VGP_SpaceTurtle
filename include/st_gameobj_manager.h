#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>
#include <components/st_transform.h>
#include <components/st_render.h>

#include <memory>

namespace ST {

	// --------------------------- Manager ----------------------------
	class GameObj_Manager{
	public:

		GameObj_Manager();
		~GameObj_Manager();
		
		ComponentId createTransformComponent();
		ComponentId createRenderComponent();

		std::unique_ptr<ST::GameObj> createGameObj(const std::vector<ComponentId> c);
		const int getGameObjNum();

		void UpdateTransforms();
		void UpdateRenderMultiThread();
		void UpdateRender(int offset = 0, int to = -1);

		//GameObj& root();

		std::vector<TransformComponent> transformComponentList_;
		std::vector<RenderComponent> renderComponentList_;
		
		//std::vector<BeltComponent> beltComponentList_; 
		//std::vector<BeltRenderPairComponent> beltRenderPairComponentList_;  // Id trans y render
		//struct BeltRender {
		//	size_t belt_id;
		//	size_t render_id;
		//};
		
		//std::vector<std::optional<RenderComponent>> renderComponentList_;
	private:

		size_t TransCompIndex_;
		size_t RenderCompIndex_;
		
		ST::Program* basicProgram;

		unsigned int numGameObjs;

		GameObj_Manager(const GameObj_Manager& o);

	};
}

#endif