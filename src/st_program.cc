#include "st_program.h"
#include <assert.h>

ST::Program::Program(){
	gladLoadGL();
	internalID = glCreateProgram();
}

GLuint ST::Program::getID() const{
	return internalID;
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
