#ifndef _SPACE_TURTLE_SYSTEM_RENDER_H_
#define _SPACE_TURTLE_SYSTEM_RENDER_H_ 1

#include <components/st_render.h>
#include <components/st_transform.h>
#include <st_camera.h>

#include <optional>

namespace ST {

	class SystemRender {
	public:
		static void Render(const std::vector<std::optional<ST::RenderComponent>>& r, const std::vector<std::optional<ST::TransformComponent>>& t, bool renderColliders = false, ST::Camera* cam = nullptr);
	private:
		SystemRender();
		~SystemRender();
		SystemRender(const SystemRender& o);
	};
}

#endif