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

		std::unique_ptr<ST::GameObj> createGameObj(std::vector<ComponentId> c);

		void UpdateTransforms();
		void UpdateRender();

		//GameObj& root();

		std::vector<TransformComponent> transformComponentList_;
		std::vector<RenderComponent> renderComponentList_;
	private:

		size_t TransCompIndex_;
		size_t RenderCompIndex_;
		
		ST::Program* basicProgram;

		GameObj_Manager(const GameObj_Manager& o);

	};
}

#endif