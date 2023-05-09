#ifndef _SPACE_TURTLE_GAMEOBJ_MANAGER_H_
#define _SPACE_TURTLE_GAMEOBJ_MANAGER_H_ 1

#include <typeindex>
#include <st_program.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <optional>

#include <st_gameobj.h>
#include <st_rendertarget.h>
#include <components/st_name.h>
#include <components/st_hierarchy.h>
//#include <st_camera.h>

#include <mat4x4.hpp>

#define MAX_OBJECTS 100000

namespace ST {
	
	class CameraComponent;

	// --------------------------- Manager ----------------------------
	class GameObj_Manager{

		struct ComponentVector {
			virtual void grow(size_t new_size) = 0;
			virtual void deleteOn(int index) = 0;
			virtual ~ComponentVector() {}
		};
		template<typename T>
		struct ComponentListImpl : ComponentVector {
			virtual void grow(size_t new_size) override { components_vector_.resize(new_size); }
			virtual void deleteOn(int index) override { 
				if (index >= 0 && index < components_vector_.size()) {
					components_vector_.at(index) = std::nullopt;
				}
			}
			std::vector<std::optional<T>> components_vector_;
		};

	public:
		GameObj_Manager();

		template<typename C>
		void addComponentClass();

		template<typename... Cs>
		ST::GameObj createGameObj(Cs... components);
		
		void deleteGameObj(int ObjID);

		template<typename C>
		ST::GameObj getGameObj(const C& component) const;

		template<typename C>
		bool addComponent(ST::GameObj ref, C component);
		template<typename C>
		bool addComponent(size_t ObjID);

		template<typename C>
		bool removeComponent(size_t ObjID);

		template<typename C>
		C* getComponent(ST::GameObj ref);
		template<typename C>
		C* getComponent(size_t ObjID);

		template<class T>
		std::vector<std::optional<T>>* getComponentVector() const;

		size_t size() const;

		// ------------------------------- TRASH ZONE ---------------------------------
		// Default Shader Program to render.
		std::shared_ptr<ST::Program> basicProgram;
		std::shared_ptr<ST::Program> unliteProgram;
		std::shared_ptr<ST::Program> shadowMapping;
		std::shared_ptr<ST::Program> framebufferProgram;
		std::shared_ptr<ST::Program> postproces_blur;
		std::shared_ptr<ST::Program> g_buffer;
		std::shared_ptr<ST::Program> skybox;

		// ***************** Shadow Mapping Test ***************
		//bool haveShadowMap_;
		//ST::RenderTarget shadowMap;
		//glm::mat4 shadowMappingMatTest;

		// ----- Camera -----
		void setMainCamera(const ST::GameObj& cam);
		int mainCameraID() const;

		// ******************* Test *******************
		int drawcalls_;

		// ------------------------------- TRASH ZONE ---------------------------------

		~GameObj_Manager();
	private:
		size_t last_gameObj_ = 0;

		using UniqueCLH = std::unique_ptr<ComponentVector>;
		using ComponentMap = std::unordered_map<std::type_index, UniqueCLH>;
		ComponentMap component_map_;

		GameObj_Manager(const GameObj_Manager& o);
		
		int mainCameraID_;
		bool rootCreated = false;

	public:
		size_t objectSelected;
		ST::GameObj root = createGameObj();
	};
}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

template<typename... Cs>
ST::GameObj ST::GameObj_Manager::createGameObj(Cs... components) {
	GameObj ref{ last_gameObj_++, *this };
	if (last_gameObj_ >= MAX_OBJECTS) {
		for (auto& [type, components_vector_] : component_map_) {
			components_vector_->grow(last_gameObj_);
		}
	}
	(addComponent<Cs>(ref, components), ...);

	addComponent<ST::NameComponent>(last_gameObj_ - 1);
	addComponent<ST::HierarchyComponent>(last_gameObj_ -1);

	//static bool rootCreated = false;
	if (rootCreated) {
		root.getComponent<ST::HierarchyComponent>()->addChild(ref);
	}else {
		rootCreated = true;
	}

	return ref;
}

template<typename C>
ST::GameObj ST::GameObj_Manager::getGameObj(const C& component) const {
	auto mut_this = const_cast<ST::GameObj_Manager*>(this);
	do {
		auto cl = mut_this->getComponentVector<C>();
		if (!cl) break;

		auto hacky_ptr = reinterpret_cast<const std::optional<C>*>(&component);
		auto begin = cl->data();
		auto end = begin + cl->size();
		if (hacky_ptr < begin || hacky_ptr >= end) break;

		auto distance = static_cast<size_t>(hacky_ptr - cl->data());
		return ST::GameObj{ distance, *mut_this };
	} while (false);
	return ST::GameObj{ ST::GameObj::null_id,*mut_this };
}

template<typename C>
std::vector<std::optional<C>>* ST::GameObj_Manager::getComponentVector() const{
	auto result = component_map_.find(std::type_index{ typeid(C) });
	if (result == component_map_.end()) return nullptr;
	auto ptr = static_cast<ComponentListImpl<C>*>(result->second.get());
	return &(ptr->components_vector_);
}

template<typename C>
void ST::GameObj_Manager::addComponentClass() {
	std::unique_ptr<ComponentVector> ptr = std::make_unique<ComponentListImpl<C>>();
	ptr->grow(MAX_OBJECTS); // ***** TEST *****
	component_map_.insert({ typeid(C) , std::move(ptr) });
}

template<typename C>
bool ST::GameObj_Manager::addComponent(ST::GameObj ref, C component) {
	auto cl = getComponentVector<C>();
	if (!cl) return false;
	cl->at(ref.getID()) = std::forward<C>(component);
	return true;
}

template<typename C>
bool ST::GameObj_Manager::addComponent(size_t ObjID) {
	auto cl = getComponentVector<C>();
	if (!cl) return false;
	C component{};
	cl->at(ObjID) = std::forward<C>(component);
	return true;
}

template<typename C>
bool ST::GameObj_Manager::removeComponent(size_t ObjID) {
	auto cl = getComponentVector<C>();
	if (!cl) return false;
	cl->at(ObjID) = std::nullopt;
	return true;
}

template<typename C>
C* ST::GameObj_Manager::getComponent(ST::GameObj ref) {
	auto cl = getComponentVector<C>();
	if (!cl) return nullptr;
	auto& c = cl->at(ref.getID());
	if (!c.has_value()) return nullptr;
	return &c.value();
}
template<typename C>
C* ST::GameObj_Manager::getComponent(size_t ObjID) {
	auto cl = getComponentVector<C>();
	if (!cl) return nullptr;
	auto& c = cl->at(ObjID);
	if (!c.has_value()) return nullptr;
	return &c.value();
}

#endif