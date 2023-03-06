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
		return false;
	}
	
	return true;
}

void ST::Program::attach(Shader &s){
	glAttachShader(internalID, s.getID());
	assert(glGetError() == GL_NO_ERROR);
}

bool ST::Program::link(){
	glLinkProgram(internalID);
	assert(glGetError() == GL_NO_ERROR);
	if (glGetError() != GL_NO_ERROR) { return false; }
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
