#ifndef _SPACE_TURTLE_GAMEOBJ_H_
#define _SPACE_TURTLE_GAMEOBJ_H_ 1

#include <vector>

#include <st_components.h>

//#include <st_gameobj_manager.h>

namespace ST {
	class GameObj_Manager;

	class GameObj{
	public:
		GameObj(size_t id, GameObj_Manager& gm) : ID_{ id }, gm_{ gm } {}

		// Basic Info
		int getID() const;
		//void setID(int id);
		
		template<typename C> C* getComponent();

		// Iterator interface
		bool operator!=(const GameObj& other) const;
		//GameObj& operator++();
		GameObj& operator*();

		// Podriamos pasarle en cuanto tiempo quieres que se destuya, como en Unity?
		// Que al llamar a esta funcion, se añanada al GameManager, a una lista para destruyir
		// y que en esa tenga el contador.
		//void Destroy();

		~GameObj();
		//GameObj(const GameObj& o);

	private:
		// The creator manager reference
		GameObj_Manager& gm_;

		static constexpr size_t null_id = 0xFFFFFFFF;

		//std::vector<ST::ComponentId> components;
		size_t ID_ = null_id;
	};
}

#endif