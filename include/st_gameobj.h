#ifndef _SPACE_TURTLE_GAMEOBJ_H_
#define _SPACE_TURTLE_GAMEOBJ_H_ 1

#include <vector>

#include <st_components.h>

namespace ST {

	class GameObj{
	public:
		GameObj();

		//void addComponent(const ST::Components* c);
		//int numComponents() const;

		~GameObj();
	private:
		GameObj(const GameObj& o);
		std::vector<ST::Components> components;
	};
}

#endif