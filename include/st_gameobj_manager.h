#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>
#include <st_components.h>

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

		//GameObj& root();

		std::vector<TransformComponent> transformComponentList_;
		std::vector<RenderComponent> renderComponentList_;
	private:

		size_t TransCompIndex_;
		size_t RenderCompIndex_;
		
		GameObj_Manager(const GameObj_Manager& o);

	};
}

#endif