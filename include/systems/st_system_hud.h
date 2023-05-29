#ifndef _SPACE_TURTLE_SYSTEM_HUD_H_
#define _SPACE_TURTLE_SYSTEM_HUD_H_ 1

#include <st_window.h>
#include <st_camera.h>
#include <st_gameobj_manager.h>
#include <st_gameobj.h>

namespace ST {

	class SystemHUD {
	public:
		/**
		*@brief Call it to show NavBar (Posibility to create objects)
		*/
		static void NavBar(ST::GameObj_Manager& gm);
		/**
		*@brief Call it to show Inspector (Show information of the object selected)
		*/
		static void Inspector(ST::GameObj_Manager& gm);
		/**
		*@brief Call it to show Hierarchy (Objects on the scene)
		*/
		static void Hierarchy(ST::GameObj_Manager& gm);
		/**
		*@brief Call it to show Stats (Basic info of the scene)
		*/
		static void Stats(const ST::Window& w, const ST::GameObj_Manager& gm);
		
	private:
		SystemHUD();
		~SystemHUD();
		SystemHUD(const SystemHUD& o);
	};
}

#endif