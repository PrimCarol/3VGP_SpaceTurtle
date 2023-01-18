#ifndef _SPACE_TURTLE_SYSTEM_TRANSFORM_H_
#define _SPACE_TURTLE_SYSTEM_TRANSFORM_H_ 1

#include <st_gameobj_manager.h>

namespace ST {

	class SystemTransform {
	public:
		static void UpdateTransforms(ST::GameObj_Manager &gm);
	private:
		SystemTransform();
		~SystemTransform();
		SystemTransform(const SystemTransform& o);
	};
}

#endif