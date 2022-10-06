#include "st_shader.h"

GLenum ShaderTypeToEnum(ST::ShaderType t) {
	switch (t){
	case ST::E_VERTEX_SHADER:
		return GL_VERTEX_SHADER;
		break;
	case ST::E_FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
		break;
	}
}

ST::Shader::Shader(ShaderType t){
	gladLoadGL();
	type = t;
	internalID = glCreateShader(ShaderTypeToEnum(t));
}

bool ST::Shader::loadSource(const char* shaderText){
	if (shaderText) {
		glShaderSource(internalID, 1, &shaderText, 0);
		glCompileShader(internalID);
	}
	if (glGetError() != GL_NO_ERROR) { return false; }
	return true;
}

GLuint ST::Shader::getID(){
	return internalID;
}

ST::Shader::~Shader(){
	glDeleteShader(internalID);
}
