#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <st_gameobj.h>
#include <st_components.h>

namespace ST {

	/*
		class Singleton
		{
		private:
		   Singleton();
		
		public:
		   static Singleton& instance()
		   {
		      static Singleton INSTANCE;
		      return INSTANCE;
		   }
		};
	*/

	// --------------------------- Manager ----------------------------
	class GameObj_Manager{
	public:

		static GameObj_Manager& instance(){
			static GameObj_Manager INSTANCE;
			return INSTANCE;
		}

		//template<typename... Component>
		//GameObj& createGameObj(Component... comp);

		ComponentId createTransformComponent();
		ComponentId createMeshComponent();
		ComponentId createMaterialComponent();

		GameObj* createGameObj(std::vector<ComponentId> c);

		//TransformComponent* getTransformComponent(size_t id);
		//MeshComponent* getMeshComponent(size_t id);
		//MaterialComponent* getMaterialComponent(size_t id);

		//GameObj& root();

		
	private:
		GameObj_Manager();
		~GameObj_Manager();

		size_t TransCompIndex_;
		size_t MeshCompIndex_;
		size_t MatCompIndex_;
		
		std::vector<TransformComponent*> transformComponentList_;
		std::vector<MeshComponent*> meshComponentList_;
		std::vector<MaterialComponent*> materialComponentList_;

		GameObj_Manager(const GameObj_Manager& o);
	};
}

#endif