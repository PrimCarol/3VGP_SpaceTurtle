#include "st_engine.h"
#include "st_opengl.h"


ST::OpenGl::OpenGl() {
	gladLoadGL();

	basic_vertex_shader = loadShader("../shaders/vertex.glslv", SHADER_VERTEX);
	basic_fragment_shader = loadShader("../shaders/fragment.glslv", SHADER_FRAGMENT);
}

ST::OpenGl::~OpenGl() {
    //glDeleteVertexArrays(1, &gVAO);
    //glDeleteBuffers(1, &gVBO);
    //glDeleteBuffers(1, &gEBO);
    //glDeleteProgram(gShaderProgram);
    //glDeleteTextures(1, &gTextureID);
}

GLuint ST::OpenGl::loadShader(const char* path, ShaderType t){
	GLuint shader = -1;
	GLchar* shader_text = (GLchar*)ST::readFile(path);
	
	switch (t){
	case ST::OpenGl::SHADER_VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ST::OpenGl::SHADER_FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	assert(glGetError() == GL_NO_ERROR);

	glShaderSource(shader, 1, &shader_text, 0);
	glCompileShader(shader);

	assert(glGetError() == GL_NO_ERROR);

	return shader;
}

GLuint ST::OpenGl::loadProgram(GLuint vertex_shader, GLuint fragment_shader){
	GLuint program = glCreateProgram();

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	assert(glGetError() == GL_NO_ERROR);

	return program;
}
