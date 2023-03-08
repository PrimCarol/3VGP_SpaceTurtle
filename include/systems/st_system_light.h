#ifndef _SPACE_TURTLE_SYSTEM_LIGHT_H_
#define _SPACE_TURTLE_SYSTEM_LIGHT_H_ 1

#include <vector>
#include <components/st_render.h>
#include <components/st_transform.h>

namespace ST {

	class GameObj_Manager;
	class Program;

	struct Light_MyObjToRender {
		ST::TransformComponent* transform_;
		ST::RenderComponent* render_;
	};

	class SystemLight {
	public:
		static void CompileLights(ST::GameObj_Manager& gm, ST::Program& p);
		static void CompileShadows(ST::GameObj_Manager& gm);
	private:

		static void setUpRender(ST::GameObj_Manager& gm);
		static void doRender(std::vector<Light_MyObjToRender>& objs);

		SystemLight();
		~SystemLight();
		SystemLight(const SystemLight& o);
	};
}

#endif