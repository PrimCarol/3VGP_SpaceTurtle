#ifndef _SPACE_TURTLE_GAMEOBJ_H_
#define _SPACE_TURTLE_GAMEOBJ_H_ 1

#include <vector>

namespace ST {
	class GameObj_Manager;

	class GameObj{
	public:
		GameObj(size_t id, GameObj_Manager& gm) : ID_{ id }, gm_{ gm } {}

		// Basic Info
		int getID() const;

		template<typename C> C* getComponent() const;
		template<typename C> bool addComponent();
		template<typename C> bool removeComponent();

		// Iterator interface
		bool operator!=(const GameObj& other) const;
		//GameObj& operator++();
		GameObj& operator*();

		~GameObj();

		static constexpr size_t null_id = 0xFFFFFFFF;

		// The creator manager reference
		GameObj_Manager& gm_;
	private:

		size_t ID_ = null_id;
	};
}

template<typename C> C* ST::GameObj::getComponent() const{
	return  ID_ == null_id ? nullptr : gm_.getComponent<C>(*this);
}

template<typename C>
inline bool ST::GameObj::addComponent(){
	gm_.addComponent<C>(ID_);
	return false;
}

template<typename C>
inline bool ST::GameObj::removeComponent(){
	gm_.removeComponent<C>(ID_);
	return false;
}

#endif