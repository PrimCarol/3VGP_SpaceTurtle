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
	};

	class SystemLight {
	public:
		/**
		*@brief Constructor
		*/
		SystemLight();

		/**
		*@brief Calculate all the lights and shadows.
		*/
		void CompileLights(ST::GameObj_Manager& gm);

		/**
		*@brief The calculated data light
		*/
		std::vector<LightsStruct> lights_;

		/**
		*@brief Destructor
		*/
		~SystemLight();
	private:

		// ******* Temporal *********
		void setUpRender(ST::GameObj_Manager& gm);
		void doRender(std::vector<Light_MyObjToRender>& objs);
		// ******* Temporal *********

		SystemLight(const SystemLight& o) {}
	};
}

#endif