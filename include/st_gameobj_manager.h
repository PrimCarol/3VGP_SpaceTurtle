#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <typeindex>
#include <st_program.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <optional>


namespace ST {
	class GameObj;

	// --------------------------- Manager ----------------------------
	class GameObj_Manager{

		struct ComponentVector {
			virtual void grow(size_t new_size) = 0;
		};
		template<typename T>
		struct ComponentListImpl : ComponentVector {
			virtual void grow(size_t new_size) override { components_vector_.resize(new_size); }
			std::vector<std::optional<T>> components_vector_;
		};

	public:
		GameObj_Manager();
		
		template<typename C>
		void addComponentClass();

		template<typename... Cs>
		ST::GameObj createGameObj(Cs... components);
		
		template<typename C>
		ST::GameObj  getGameObj(const C& component) const;

		template<typename C>
		bool addComponent(ST::GameObj ref, C component);

		template<class T>
		std::vector<std::optional<T>>* getComponentVector();

		size_t size() const;

		~GameObj_Manager();
	private:
		size_t last_gameObj_ = 0;

		using UniqueCLH = std::unique_ptr<ComponentVector>;
		using ComponentMap = std::unordered_map<std::type_index, UniqueCLH>;
		ComponentMap component_map_;

		std::shared_ptr<ST::Program> basicProgram; // Default Shader Program to render.

		GameObj_Manager(const GameObj_Manager& o);
	};
}

#endif