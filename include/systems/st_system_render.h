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
		static void Render(ST::GameObj_Manager& gm);
	private:
		SystemRender();

		//using setupUniformsCallType = bool (ST::Material& mat, ST::TransformComponent* t, MyCamera& cam);
		//static void setUpRender(ST::GameObj_Manager& gm/*, std::vector<std::optional<ST::RenderComponent>>& render, std::vector<std::optional<ST::TransformComponent>>& transform*/, MyCamera& cam);
		static void doRender(std::vector<MyObjToRender>& objs, MyCamera& cam, ST::GameObj_Manager& gm);
		static bool setUpUniforms(ST::Material& mat, ST::TransformComponent* t, MyCamera& cam, ST::GameObj_Manager& gm);

		//~SystemRender();
		SystemRender(const SystemRender& o);
	};
}

#endif