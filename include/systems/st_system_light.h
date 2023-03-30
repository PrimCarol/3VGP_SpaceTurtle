#ifndef _SPACE_TURTLE_SYSTEM_LIGHT_H_
#define _SPACE_TURTLE_SYSTEM_LIGHT_H_ 1

#include <vector>
#include <components/st_render.h>
#include <components/st_transform.h>

#include <imgui.h>

namespace ST {

	class GameObj_Manager;
	class Program;
	class RenderTarget;

	// ******* Temporal *********
	struct Light_MyObjToRender {
		ST::TransformComponent* transform_;
		ST::RenderComponent* render_;
	};
	// ******* Temporal *********

	struct Light_ShadowMap {
		std::vector<RenderTarget> renderTarget_;
		glm::mat4 matrix_;
	};

	class SystemLight {
	public:
		SystemLight();

		void CompileShadows(ST::GameObj_Manager& gm);
		void CompileLights(ST::GameObj_Manager& gm, ST::Program& p);

		glm::ivec2 textureSize_;

		~SystemLight();
	private:
		
		std::vector<Light_ShadowMap> shadowMaps_;

		// ******* Temporal *********
		void setUpRender(ST::GameObj_Manager& gm);
		void doRender(std::vector<Light_MyObjToRender>& objs);
		// ******* Temporal *********

		SystemLight(const SystemLight& o) {}
	};
}

#endif