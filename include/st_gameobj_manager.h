#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>

#include <st_program.h>
#include <memory>
#include <map>
#include <optional>

struct ComponentVector {};
template<typename T>
struct ComponentVector_Implementation : ComponentVector {
	std::vector<std::optional<T>> vector;
};

namespace ST {

	// --------------------------- Manager ----------------------------
	class GameObj_Manager{
	public:
		GameObj_Manager();
		
		std::unique_ptr<ST::GameObj> createGameObj();
		
		const int getGameObjNum();
		
		std::vector<GameObj*> GameObjsList_;

		template<class T>
		std::vector<std::optional<T>>* GetComponentVector();

		~GameObj_Manager();
	private:
		std::map<size_t, std::unique_ptr<ComponentVector> > components_map;

		std::shared_ptr<ST::Program> basicProgram; // Default Shader Program to render.

		GameObj_Manager(const GameObj_Manager& o);
	};
}

#endif