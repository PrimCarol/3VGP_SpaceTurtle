#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>
#include <st_components.h>

namespace ST {

	class GameObj_Manager{
	public:
		GameObj_Manager();

		template<typename... Component>
		GameObj& createGameObj(Component... comp);

		//GameObj& root();

		~GameObj_Manager();
	private:
		GameObj_Manager(const GameObj_Manager& o);
	};
}

#endif