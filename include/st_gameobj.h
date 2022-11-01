#ifndef _SPACE_TURTLE_GAMEOBJ_H_
#define _SPACE_TURTLE_GAMEOBJ_H_ 1

#include <vector>

#include <st_components.h>

namespace ST {

	class GameObj{
	public:
		GameObj();

		void addComponent(const ST::Components* c);
		int numComponents() const;

		//template<class c>
		//c* getComponent();

		~GameObj();
	private:
		GameObj(const GameObj& o);
		std::vector<ST::Components> components;
	};

	//template<class c>
	//inline c* GameObj::getComponent(){
	//	for (int i = 0; i < components.size(); i++){
	//		c* result = dynamic_cast<c*>(components[i]);
	//		
	//		if (result) {
	//			printf("Tengo el componente que pide.\n");
	//			return result;
	//		}
	//	}
	//	return NULL;
	//}
}

#endif