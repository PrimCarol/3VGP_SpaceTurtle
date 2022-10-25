#ifndef _SPACE_TURTLE_GAMEOBJ_H_
#define _SPACE_TURTLE_GAMEOBJ_H_ 1

namespace ST {

	class GameObj{
	public:
		GameObj();

		~GameObj();
	private:
		GameObj(const GameObj& o);
	};
}

#endif