#ifndef _SPACE_TURTLE_SHADER_H_
#define _SPACE_TURTLE_SHADER_H_ 1

#include <glad.h>

namespace ST {

	enum ShaderType{
		E_VERTEX_SHADER,
		E_FRAGMENT_SHADER
	};

	static GLchar* basic_vShader_text =
		"#version 330\n"
		"layout (location=0) in vec3 a_position;\n"
		"layout (location=1) in vec3 a_color;\n"
		"uniform mat4 u_m_trans;\n"
		"out vec3 color;\n"
		"void main() {\n"
		"color = a_color;\n"
		"gl_Position = u_m_trans * vec4(a_position, 1);\n"
		"}\n";
	static GLchar* basic_fShader_text =
		"#version 330\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"void main() {\n"
		"FragColor = vec4(color, 1.0);\n"
		"}\n";

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