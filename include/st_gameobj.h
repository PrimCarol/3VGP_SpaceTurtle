#ifndef _SPACE_TURTLE_GAMEOBJ_H_
#define _SPACE_TURTLE_GAMEOBJ_H_ 1

#include <vector>

#include <st_components.h>

namespace ST {

	class GameObj{
	public:
		GameObj();

		// Basic Info
		int getID() const;
		void setID(int id);

		// The creator manager reference
		class GameObj_Manager* gm_;

		// --- Components ---
		//class HierarchyComponent* getComponentHierarchy();
		//class TransformComponent* getComponentTransform();
		//class RenderComponent* getComponentRender();
		
		template<class T>
		T* getComponent();

		void addComponents(std::vector<ComponentId> c);

		template<class T>
		void addComponents(T* component);

		// Podriamos pasarle en cuanto tiempo quieres que se destuya, como en Unity?
		// Que al llamar a esta funcion, se añanada al GameManager, a una lista para destruyir
		// y que en esa tenga el contador.
		//void Destroy();

		~GameObj();
		//GameObj(const GameObj& o);

	private:
		std::vector<ST::ComponentId> components;
		int ID_;
	};
}

#endif