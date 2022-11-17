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
		"layout (location=1) in vec3 a_normals;\n"
		"layout (location=2) in vec2 a_uv;\n"

		"uniform mat4 u_view_matrix;\n"
		"uniform mat4 u_projection_matrix;\n"	
	    "uniform mat4 u_vp_matrix;\n"

		"uniform mat4 u_m_trans;\n"
		"uniform vec3 u_color;\n"

		"out vec3 color;\n"
		"out vec2 texCoords;\n"
		
		"void main() {\n"
			"color = u_color;\n"
			"texCoords = a_uv;\n"
			
			"gl_Position = (u_vp_matrix * u_m_trans) * vec4(a_position, 1);\n"
		"}\n";

	static GLchar* basic_fShader_text =
		"#version 330\n"
		
		"out vec4 FragColor;\n"

		"in vec3 color;\n"
		"in vec2 texCoords;\n"

		// Texture
		"uniform bool u_haveAlbedo;\n"
		"uniform sampler2D u_tex_Albedo;\n"

		"void main() {\n"
			"if(u_haveAlbedo){ FragColor = texture(u_tex_Albedo, texCoords) + vec4(color,1.0); }\n"
			"else { FragColor = vec4(color, 1.0); }\n"
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