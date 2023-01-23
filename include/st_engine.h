#ifndef _SPACE_TURTLE_ENGINE_H_
#define _SPACE_TURTLE_ENGINE_H_ 1

#include <iostream>
#include <sys/stat.h>
#include <assert.h>

#include <st_window.h>
#include <st_gameobj_manager.h>

#include <systems/st_system_render.h>
#include <systems/st_system_transform.h>
#include <systems/st_system_picking.h>
#include <systems/st_system_hud.h>

namespace ST {

	class Engine{
	public:
	
		static const float getRandom(float min, float max);
		static const unsigned char* readFile(const char* filename);

	private:
		Engine();
		~Engine();
	};

	
}

#endif