#ifndef _SPACE_TURTLE_SHADER_H_
#define _SPACE_TURTLE_SHADER_H_ 1

#include <glad.h>

namespace ST {

	class Shader{
	public:
		Shader();
		

		~Shader();
	private:

		Shader(const Shader& o);
	};
}

#endif