#ifndef _SPACE_TURTLE_SHADER_H_
#define _SPACE_TURTLE_SHADER_H_ 1

#include <glad.h>

namespace ST {

	enum ShaderType{
		E_VERTEX_SHADER,
		E_FRAGMENT_SHADER,
		E_GEOMETRY_SHADER
	};

	class Shader{
	public:
		Shader(ShaderType t);
		
		bool loadSource(const char* shaderText);
		GLuint getID();

		~Shader();
	private:
		GLuint internalID;
		ShaderType type;

		Shader(const Shader& o);
	};
}

#endif