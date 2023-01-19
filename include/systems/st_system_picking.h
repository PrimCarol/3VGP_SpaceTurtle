#ifndef _SPACE_TURTLE_SYSTEM_PICKING_H_
#define _SPACE_TURTLE_SYSTEM_PICKING_H_ 1

#include <st_window.h>
#include <st_camera.h>
#include <st_gameobj_manager.h>

namespace ST {

	class SystemPicking {
	public:
		static ST::GameObj* tryPickObj(const ST::GameObj_Manager& gm, const ST::Camera& c);
	private:
		SystemPicking();
		~SystemPicking();
		SystemPicking(const SystemPicking& o);
	};
}

#endif