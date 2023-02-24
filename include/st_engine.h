#ifndef _SPACE_TURTLE_ENGINE_H_
#define _SPACE_TURTLE_ENGINE_H_ 1

#include <iostream>
#include <sys/stat.h>
#include <assert.h>

#include <st_window.h>
#include <st_gameobj_manager.h>

#include <components/st_transform.h>
#include <components/st_hierarchy.h>
#include <components/st_name.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_light.h>

#include <systems/st_system_transform.h>
#include <systems/st_system_render.h>
#include <systems/st_system_light.h>
#include <systems/st_system_picking.h>
#include <systems/st_system_hud.h>

namespace ST {

	class Engine{
	public:
	
		/* Get a random float value between the min and max. */
		static const float getRandom(float min, float max);
		/* Read the file in the path you pass */
		static const unsigned char* readFile(const char* filename);

		static void createEmptyObj(ST::GameObj_Manager& gm);
		static void createTriangle(ST::GameObj_Manager& gm);
		static void createQuad(ST::GameObj_Manager& gm);
		static void createCircle(ST::GameObj_Manager& gm);
		static void createCube(ST::GameObj_Manager& gm);

		static void createDirectLight(ST::GameObj_Manager& gm);
		static void createPointLight(ST::GameObj_Manager& gm);
		static void createSpotLight(ST::GameObj_Manager& gm);

	private:
		Engine();
		~Engine();
	};
}

#endif