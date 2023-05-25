#include "st_program.h"
#include <assert.h>

#include <st_engine.h>

ST::Program::Program(){
	//gladLoadGL();
	internalID = glCreateProgram();
}

GLuint ST::Program::getID() const{
	return internalID;
}

bool ST::Program::setUp(const char* vertexShader, const char* fragmentShader){
	
	ST::Shader vertex(E_VERTEX_SHADER);
	GLchar* textVertex = (GLchar*)ST::Engine::readFile(vertexShader);
	if (!vertex.loadSource(textVertex)) {
		return false;
	}
	free(textVertex);

	ST::Shader fragment(E_FRAGMENT_SHADER);
	GLchar* textFragment = (GLchar*)ST::Engine::readFile(fragmentShader);
	if (!fragment.loadSource(textFragment)) {
		return false;
	}
	free(textFragment);

	attach(vertex);
	attach(fragment);
	if (!link()) {
		//glDetachShader(internalID, vertex.getID());
		//glDetachShader(internalID, fragment.getID());
		glDeleteProgram(internalID);
		return false;
	}
	
	return true;
}

bool ST::Program::setUp(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath){
	ST::Shader vertex(E_VERTEX_SHADER);
	GLchar* textVertex = (GLchar*)ST::Engine::readFile(vertexShaderPath);
	if (!vertex.loadSource(textVertex)) {
		return false;
	}
	free(textVertex);

	ST::Shader fragment(E_FRAGMENT_SHADER);
	GLchar* textFragment = (GLchar*)ST::Engine::readFile(fragmentShaderPath);
	if (!fragment.loadSource(textFragment)) {
		return false;
	}
	free(textFragment);

	ST::Shader geometry(E_GEOMETRY_SHADER);
	GLchar* textGeometry = (GLchar*)ST::Engine::readFile(geometryShaderPath);
	if (!geometry.loadSource(textGeometry)) {
		return false;
	}
	free(textGeometry);

	attach(vertex);
	attach(fragment);
	attach(geometry);
	if (!link()) {
		glDeleteProgram(internalID);
		//glDetachShader(internalID, vertex.getID());
		//glDetachShader(internalID, fragment.getID());
		//glDetachShader(internalID, geometry.getID());
		return false;
	}

	return true;
}

void ST::Program::attach(Shader &s){
	glAttachShader(internalID, s.getID());
	assert(glGetError() == GL_NO_ERROR);
}

bool ST::Program::link(){
	/*glLinkProgram(internalID);
	assert(glGetError() == GL_NO_ERROR);
	if (glGetError() != GL_NO_ERROR) { return false; }
	return true;*/
	GLint compile_me = -1;
	GLint max_length = 0;
	std::string output_log;

	glLinkProgram(internalID);
	glGetProgramiv(internalID, GL_LINK_STATUS, &compile_me);

	glGetProgramiv(internalID, GL_INFO_LOG_LENGTH, &max_length);
	glGetProgramInfoLog(internalID, static_cast<GLsizei>(output_log.capacity()), &max_length, output_log.data());

	if (max_length > 0) {
		printf("Error in Program Link Function:\n%s\n", output_log.c_str());
	}

	if (compile_me != GL_TRUE) {
		glDeleteProgram(internalID);
		return false;
	}

	return true;
}

void ST::Program::use() const{
	glUseProgram(internalID);
}

int ST::Program::getAttrib(const char* location) const{
	return glGetAttribLocation(internalID, location);
}

GLuint ST::Program::getUniform(const char* location) const{
	return glGetUniformLocation(internalID, location);
}

ST::Program::~Program(){
	glDeleteProgram(internalID);
}

ST::Program::Program(const Program& o){
	internalID = o.internalID;
}
