#ifndef _SPACE_TURTLE_SYSTEM_CAMERA_H_
#define _SPACE_TURTLE_SYSTEM_CAMERA_H_ 1

namespace ST {

	class GameObj_Manager;

	class SystemCamera {
	public:
		static void UpdateCamera(ST::GameObj_Manager& gm);
	private:
		SystemCamera();
		~SystemCamera();
		SystemCamera(const SystemCamera& o);
	};
}

#endif