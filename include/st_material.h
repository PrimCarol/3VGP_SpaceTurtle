#ifndef _SPACE_TURTLE_MATERIAL_H_
#define _SPACE_TURTLE_MATERIAL_H_ 1

#include <glm.hpp>
#include <st_program.h>

namespace ST {

	class Material{
	public:
		Material();
		
		void setColor(glm::vec3 rgb);
		const glm::vec3 getColor();

		const ST::Program* getProgram();

		~Material();
		Material(const Material& o);
	
	private:
		glm::vec3 color;
		ST::Program* program;
	};
}

#endif