#ifndef _SPACE_TURTLE_SYSTEM_RENDER_H_
#define _SPACE_TURTLE_SYSTEM_RENDER_H_ 1

#include <components/st_render.h>
#include <components/st_transform.h>
#include <st_camera.h>

#include <optional>

namespace ST {

	struct MyObjToRender{
		ST::TransformComponent* transform_;
		ST::RenderComponent* render_;
	};
	
	class GameObj_Manager;

	class SystemRender {
	public:
		static void Render(ST::GameObj_Manager& gm, ST::Camera* cam = nullptr);

	private:
		SystemRender();

		static void setUpRender(std::vector<std::optional<ST::RenderComponent>>& r, std::vector<std::optional<ST::TransformComponent>>& t, ST::Camera& cam);
		static void doRender(std::vector<MyObjToRender>& objs, ST::Camera& cam);

		static bool setUpUniforms(ST::Material& mat, ST::TransformComponent* t, ST::Camera& cam);

		//~SystemRender();
		SystemRender(const SystemRender& o);
	};
}

#endif