#ifndef _SPACE_TURTLE_SYSTEM_RENDER_H_
#define _SPACE_TURTLE_SYSTEM_RENDER_H_ 1

#include <components/st_render.h>
#include <components/st_transform.h>
#include <components/st_camera.h>

#include <optional>

namespace ST {

	struct MyObjToRender{
		ST::TransformComponent* transform_;
		ST::RenderComponent* render_;
	};

	struct MyCamera {
		ST::TransformComponent* transform_;
		ST::CameraComponent* cam_;
	};
	
	class GameObj_Manager;

	class SystemRender {
	public:
		/**
		*@brief Render the scene that has the same program as the one you want
		*/
		static void Render(ST::GameObj_Manager& gm, const ST::Program& p);
	private:
		SystemRender();

		static void doRender(std::vector<MyObjToRender>& objs, MyCamera& cam, ST::GameObj_Manager& gm);
		static bool setUpUniforms(ST::Material& mat, ST::TransformComponent* t, MyCamera& cam, ST::GameObj_Manager& gm);

		SystemRender(const SystemRender& o);
	};
}

#endif