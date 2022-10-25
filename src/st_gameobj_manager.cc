#include <st_gameobj_manager.h>

#include <type_traits>
#include <utility>

template<typename ...Component>
inline ST::GameObj& ST::GameObj_Manager::createGameObj(Component ...comp){
	static_assert(true && ... && std::is_base_of<Component, Component>::value);
	Entity e{ std::fordware<Patata>(patata)... };
	return e;
}