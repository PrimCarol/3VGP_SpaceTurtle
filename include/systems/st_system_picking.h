#ifndef _SPACE_TURTLE_SYSTEM_PICKING_H_
#define _SPACE_TURTLE_SYSTEM_PICKING_H_ 1

#include <st_window.h>
#include <st_camera.h>
#include <st_gameobj_manager.h>

namespace ST {

	class SystemPicking {
	public:
		/* Return the reference of the object */
		static ST::GameObj* tryPickObj(const ST::Window& w, const ST::GameObj_Manager& gm, const ST::Camera* c = nullptr);
	private:
		SystemPicking();
		~SystemPicking();
		SystemPicking(const SystemPicking& o);
	};
}

#endif