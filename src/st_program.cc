#include "st_program.h"

ST::Program::Program(){
	gladLoadGL();
	internalID = glCreateProgram();
}

GLuint ST::Program::getID() const{
	return internalID;
}

void ST::Program::attach(Shader &s){
	glAttachShader(internalID, s.getID());
}

bool ST::Program::link(){
	glLinkProgram(internalID);
	if (glGetError() != GL_NO_ERROR) { return true; }
	return false;
}

void ST::Program::use() const{
	glUseProgram(internalID);
}

int ST::Program::getAttrib(const char* location) const{
	return glGetAttribLocation(internalID, location);
}

int ST::Program::getUniform(const char* location) const{
	return glGetUniformLocation(internalID, location);
}

ST::Program::~Program(){
	glDeleteProgram(internalID);
}
