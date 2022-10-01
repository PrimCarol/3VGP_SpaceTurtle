#include "st_opengl.h"
#include <st_utilities.h>

ST::OpenGl::OpenGl() {
	gladLoadGL();
	if (glGetError() == GL_NO_ERROR) {
		printf("Cargo OpenGL\n");
	}
	//basic_vertex_shader = loadShader("../shaders/vertex.vert", SHADER_VERTEX);
	//basic_fragment_shader = loadShader("../shaders/fragment.frag", SHADER_FRAGMENT);
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
		printf("vertex\n");
		break;
	case ST::OpenGl::SHADER_FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		printf("fragment\n");
		break;
	}
	//printf(" %s \n", shader_text);
	assert(glGetError() == GL_NO_ERROR);

	glShaderSource(shader, 1, &shader_text, NULL);
	glCompileShader(shader);

	//char* log = new char[255];
	//glGetShaderInfoLog(shader, 255, NULL, log);

	//printf("Compiling... %s \n", log);

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

GLuint ST::OpenGl::loadMesh(VertexInfo* meshInfo, unsigned int* indices){
	GLuint vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(meshInfo), &meshInfo, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	assert(glGetError() == GL_NO_ERROR);
	
	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	assert(glGetError() == GL_NO_ERROR);
	
	//glBindVertexArray(0);

	return vertexArray;
}

void ST::OpenGl::drawObj(GLuint program, GLuint mesh){
	glUseProgram(program);
	glBindVertexArray(mesh);
	//printf("Voy a dibujar con el program %d y el mesh %d \n", program, mesh);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//void ST::OpenGl::useProgram(GLuint program){
//	glUseProgram(program);
//}
