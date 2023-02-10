#ifndef _SPACE_TURTLE_SYSTEM_HUD_H_
#define _SPACE_TURTLE_SYSTEM_HUD_H_ 1

#include <st_window.h>
#include <st_camera.h>
#include <st_gameobj_manager.h>
#include <st_gameobj.h>

namespace ST {

	class SystemHUD {
	public:
		static void Inspector(ST::GameObj_Manager& gm, const size_t objSeletected);
		static void Hierarchy(const ST::Window& w, ST::GameObj_Manager& gm, ST::GameObj* objSeletected = nullptr);
		static void Stats(const ST::Window& w, const ST::GameObj_Manager& gm);
		
		// Work in progress...
		//static void EditTransform(const ST::Camera& c, ST::GameObj* objSeletected = nullptr, bool editTransformDecomposition = false);
	private:
		SystemHUD();
		~SystemHUD();
		SystemHUD(const SystemHUD& o);
	};
}

#endif