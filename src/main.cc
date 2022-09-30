#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <st_engine.h>


// -----------------------------------------------------------------------------------------------------------


static GLuint gShaderProgram = 0;
static GLuint gVBO = 0, gVAO = 0;
static GLuint gEBO = 0;
static GLuint gTextureID = 0;

struct Vertex {
	float x, y, z;
	float r, g, b;
};

Vertex vertices[] = {
	{ 0.5f, 0.5f,0.0f  ,  1.0f,0.0f,0.0f},
	{ 0.5f,-0.5f,0.0f  ,  0.0f,1.0f,0.0f},
	{-0.5f,-0.5f,0.0f  ,  0.0f,0.0f,1.0f},
	{-0.5f, 0.5f,0.0f  ,  1.0f,1.0f,1.0f}
};

unsigned int indices[] = { 0,1,2  ,  0,2,3 };

float rotation = 0.0f;

void onInit() {
	//ST::OpenGl& op = ST::OpenGL::Instance();

	/*GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
	GLchar* v_text = (GLchar*)ST::readFile("../shaders/vertex.glslv");
	glShaderSource(v_shader, 1, &v_text, 0);
	glCompileShader(v_shader);
	assert(glGetError() == GL_NO_ERROR);

	GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	GLchar* f_text = (GLchar*)ST::readFile("../shaders/fragment.glslf");
	glShaderSource(f_shader, 1, &f_text, 0);
	glCompileShader(f_shader);
	assert(glGetError() == GL_NO_ERROR);*/


	//gShaderProgram = glCreateProgram();
	//glAttachShader(gShaderProgram, v_shader);
	//glAttachShader(gShaderProgram, f_shader);
	//glLinkProgram(gShaderProgram);
	//assert(glGetError() == GL_NO_ERROR);


	/*glGenVertexArrays(1, &gVAO);
	glBindVertexArray(gVAO);

	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	assert(glGetError() == GL_NO_ERROR);

	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	assert(glGetError() == GL_NO_ERROR);
	printf("Shaders y cositas done.");*/
}

void onFrame() {
	/*glUseProgram(gShaderProgram);
	glBindVertexArray(gVAO);

	GLint location = glGetUniformLocation(gShaderProgram, "CustomData");
	glUniform1f(location, rotation);
	assert(glGetError() == GL_NO_ERROR);


	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
}

// -----------------------------------------------------------------------------------------------------------


int main(){
	printf("-- Welcome to Space Turtle --\n");
	
	// Window
	ST::Window* w = new ST::Window(1090, 720);
	w->Focus();

	float c[3] = {1.0f,0.8f,0.9f};



	onInit();



	while (w->isOpen()){
		
		w->ColorBg(sin(c[0]), sin(c[1]), sin(c[2]));

		//if (w->isDown(ST::ST_INPUT::ST_INPUT_UP)) {
		//	printf("Aprieto\n");
		//}
		
		if (w->isKeyPressed(GLFW_KEY_R)) {
			printf("Mantengo\n");
			c[0] += 0.1f;
		}
		if (w->isKeyPressed(GLFW_KEY_G)) {
			//printf("Mantengo\n");
			c[1] += 0.1f;
		}
		if (w->isKeyPressed(GLFW_KEY_B)) {
			//printf("Mantengo\n");
			c[2] += 0.1f;
		}
		if (w->isKeyPressed(GLFW_KEY_J)) {
			//printf("Mantengo\n");
			rotation += 0.05f;
		}
		//if (w->isKeyReless(GLFW_KEY_J)) {
		//	printf("Suelto\n");
		//}
		
		//if (w->isMouseDown(0) || w->isMouseDown(1)) {
		//	printf("Mouse-> Aprieto\n");
		//}
		//
		//if (w->isMousePressed(0) || w->isMousePressed(1)) {
		//	printf("Mouse-> Mantengo\n");
		//}
		//
		//if (w->isMouseReless(0) || w->isMouseReless(1)) {
		//	printf("Mouse-> Suelto\n");
		//}

		//if (w->isInputDown(ST::ST_INPUT_KEY_UP)) {
		//	printf("UWU\n");
		//}

		//printf("Mouse x: %f  -  y: %f \n", w->mousePosX(), w->mousePosY());

		// -------------- TRIANGLE ------------------

		//glBegin(GL_TRIANGLES);
		//glVertex2f( 0.2f,  0.2f);
		//glVertex2f(-0.2f,  0.2f);
		//glVertex2f( 0.0f, -0.2f);
		//glEnd();

		onFrame();

		w->Render();
	}

	delete w;

	printf("Bye!\n");
	return 0;
}