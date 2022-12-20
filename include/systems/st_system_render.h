#ifndef _SPACE_TURTLE_SYSTEM_RENDER_H_
#define _SPACE_TURTLE_SYSTEM_RENDER_H_ 1

#include <components/st_render.h>
#include <components/st_transform.h>
#include <st_camera.h>

namespace ST {

	class SystemRender {
	public:
		static void Render(ST::Camera* cam, std::vector<ST::RenderComponent> r, std::vector<ST::TransformComponent> t);
	private:
		SystemRender();
		~SystemRender();
		SystemRender(const SystemRender& o);
	};
}

#endif