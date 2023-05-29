#ifndef _SPACE_TURTLE_SYSTEM_CAMERA_H_
#define _SPACE_TURTLE_SYSTEM_CAMERA_H_ 1

namespace ST {

	class GameObj_Manager;
	class Window;

	class SystemCamera {
	public:
		/**
		*@brief Call it to update the position of the camera.
		*/
		static void UpdateCamera(ST::GameObj_Manager& gm);
		/**
		*@brief Call it to have the posibility to move the camera with FPS style.
		*/
		static void Movemment(ST::GameObj_Manager& gm, ST::Window& w, float MoveSpeed = 30.0f, float RotateSpeed = 50.0f);
	private:
		SystemCamera();
		~SystemCamera();
		SystemCamera(const SystemCamera& o);
	};
}

#endif