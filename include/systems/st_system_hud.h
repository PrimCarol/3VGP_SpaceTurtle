#ifndef _SPACE_TURTLE_SYSTEM_HUD_H_
#define _SPACE_TURTLE_SYSTEM_HUD_H_ 1

#include <st_window.h>
#include <st_gameobj_manager.h>
#include <st_gameobj.h>

namespace ST {

	class SystemHUD {
	public:
		static void DrawHud(const ST::Window& w, ST::GameObj_Manager& gm, ST::GameObj* objSeletected = nullptr);
	private:
		SystemHUD();
		~SystemHUD();
		SystemHUD(const SystemHUD& o);
	};
}

#endif