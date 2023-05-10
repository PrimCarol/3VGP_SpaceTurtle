#ifndef _SPACE_TURTLE_SYSTEM_LIGHT_H_
#define _SPACE_TURTLE_SYSTEM_LIGHT_H_ 1

#include <vector>
#include <components/st_render.h>
#include <components/st_transform.h>
#include <components/st_light.h>
#include <st_shadowmapping.h>

#include <imgui.h>

namespace ST {

	class GameObj_Manager;
	class Program;

	// ******* Temporal *********
	struct Light_MyObjToRender {
		ST::TransformComponent* transform_;
		ST::RenderComponent* render_;
	};
	// ******* Temporal *********

	struct LightsStruct {
		ST::LightComponent* light_;
		std::vector<ST::ShadowMapping> renderTarget_;
		std::vector<glm::mat4> matrix_;
	};
	//struct Light_ShadowMap {
	//	std::vector<ST::ShadowMapping> renderTarget_;
	//	glm::mat4 matrix_;
	//};

	class SystemLight {
	public:
		SystemLight();

		//void CompileShadows(ST::GameObj_Manager& gm);
		//void CompileLights(ST::GameObj_Manager& gm, ST::Program& p);
		void CompileLights(ST::GameObj_Manager& gm);

		glm::ivec2 textureSize_; // Temporal, poner en cada luz.

		std::vector<LightsStruct> lights_;

		~SystemLight();
	private:

		//std::vector<Light_ShadowMap> shadowMaps_;

		// ******* Temporal *********
		void setUpRender(ST::GameObj_Manager& gm);
		void doRender(std::vector<Light_MyObjToRender>& objs);
		// ******* Temporal *********

		SystemLight(const SystemLight& o) {}
	};
}

#endif