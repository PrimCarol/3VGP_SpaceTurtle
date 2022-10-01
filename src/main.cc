#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <st_engine.h>

// -----------------------------------------------------------------------------------------------------------


static GLuint gShaderProgram = 0;
static GLuint gMesh = 0;

ST::OpenGl::VertexInfo vertices[] = {
	{ 0.5f, 0.5f,0.0f  ,  1.0f,0.0f,0.0f},
	{ 0.5f,-0.5f,0.0f  ,  0.0f,1.0f,0.0f},
	{-0.5f,-0.5f,0.0f  ,  0.0f,0.0f,1.0f},
	{-0.5f, 0.5f,0.0f  ,  1.0f,1.0f,1.0f}
};

unsigned int indices[] = { 0,1,2  ,  0,2,3 };

void onInit() {

	GLuint vShader, fShader;
	vShader = ST::OpenGl::Instance().loadShader("../shaders/vertex.vert", ST::OpenGl::SHADER_VERTEX);
	fShader = ST::OpenGl::Instance().loadShader("../shaders/fragment.frag", ST::OpenGl::SHADER_FRAGMENT);
	printf("Shaders -> %d - %d \n", vShader, fShader);

	gShaderProgram = ST::OpenGl::Instance().loadProgram(vShader,fShader);
	printf("Program -> %d \n", gShaderProgram);

	gMesh = ST::OpenGl::Instance().loadMesh(vertices, indices);
	printf("Mesh -> %d \n", gMesh);

	printf("Shaders y cositas done.\n");
}

void onFrame() {
	ST::OpenGl::Instance().drawObj(gShaderProgram, gMesh);
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
			//printf("Mantengo\n");
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

		onFrame();

		w->Render();
	}

	delete w;

	printf("Bye!\n");
	return 0;
}