#ifndef _SPACE_TURTLE_SYSTEM_LIGHT_H_
#define _SPACE_TURTLE_SYSTEM_LIGHT_H_ 1

namespace ST {

	class GameObj_Manager;
	class Program;

	class SystemLight {
	public:
		static void CompileLights(ST::GameObj_Manager& gm, ST::Program& p);
	private:
		SystemLight();
		~SystemLight();
		SystemLight(const SystemLight& o);
	};
}

#endif