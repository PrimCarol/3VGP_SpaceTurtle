#ifndef _SPACE_TURTLE_SYSTEM_HUD_H_
#define _SPACE_TURTLE_SYSTEM_HUD_H_ 1

#include <st_window.h>
#include <st_camera.h>
#include <st_gameobj_manager.h>
#include <st_gameobj.h>

namespace ST {

	class SystemHUD {
	public:
		static void NavBar(ST::GameObj_Manager& gm);
		static void Inspector(ST::GameObj_Manager& gm);
		static void Hierarchy(ST::GameObj_Manager& gm);
		static void Stats(const ST::Window& w, const ST::GameObj_Manager& gm);
		
	private:
		SystemHUD();
		~SystemHUD();
		SystemHUD(const SystemHUD& o);
	};
}

#endif