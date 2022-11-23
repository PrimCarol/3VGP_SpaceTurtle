#ifndef _SPACE_TURTLE_GAMEOBJ_H_
#define _SPACE_TURTLE_GAMEOBJ_H_ 1

#include <vector>

#include <st_components.h>

namespace ST {

	class GameObj{
	public:
		GameObj();

		// Basic Info
		int getID();
		void setID(int id);

		// The creator manager reference
		class GameObj_Manager* gm_;

		// --- Components ---
		void checkComponents();
		ST::Components* getComponent(ST::CompType t);		
		std::vector<ST::ComponentId> components;

		// Podriamos pasarle en cuanto tiempo quieres que se destuya, como en Unity?
		// Que al llamar a esta funcion, se a�anada al GameManager, a una lista para destruyir
		// y que en esa tenga el contador.
		//void Destroy();

		~GameObj();
		//GameObj(const GameObj& o);

	private:
		int ID_;
	};
}

#endif


// ************* Crear un componente ***********

//GameObj* parent;
//std::vector<GameObj*> childs;

// --- Childs ---
//void addChild(GameObj* c);
//void removeChild(const unsigned int index);
//GameObj* getChild(const unsigned int index);
//GameObj* getParent();