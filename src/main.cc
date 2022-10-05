#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctime>

#include <st_engine.h>

#include <st_triangle.h>

// -----------------------------------------------------------------------------------------------------------

/*static GLuint gShaderProgram = 0;
static GLuint gMesh = 0;

ST::OpenGl::VertexInfo vertices[] = {
	{ 0.5f, 0.5f,0.0f  ,  1.0f,0.0f,0.0f},
	{ 0.5f,-0.5f,0.0f  ,  0.0f,1.0f,0.0f},
	{-0.5f,-0.5f,0.0f  ,  0.0f,0.0f,1.0f},
	{-0.5f, 0.5f,0.0f  ,  1.0f,1.0f,1.0f}
};

unsigned int indices[] = { 0,1,2  ,  0,2,3 };

void onInit() {
	gladLoadGL();

	// ------- Shaders -------
	GLuint vShader, fShader;
	vShader = ST::OpenGl::Instance().loadShader("../shaders/vertex.vert", ST::OpenGl::SHADER_VERTEX);
	fShader = ST::OpenGl::Instance().loadShader("../shaders/fragment.frag", ST::OpenGl::SHADER_FRAGMENT);
	
	printf("Shaders -> %d - %d \n", vShader, fShader);

	// ------- Program -------
	gShaderProgram = ST::OpenGl::Instance().loadProgram(vShader,fShader);
	printf("Program -> %d \n", gShaderProgram);

	// ------- Mesh -------
	//gMesh = ST::OpenGl::Instance().loadMesh(*vertices, *indices);
	
	glGenVertexArrays(1, &gMesh);
	glBindVertexArray(gMesh);

	GLuint gVBO = 0;
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	//int a = sizeof(vertices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ST::OpenGl::VertexInfo), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ST::OpenGl::VertexInfo), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	GLuint gEBO = 0;
	glGenBuffers(1, &gEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
	//int b = sizeof(indices);

	printf("Mesh -> %d \n", gMesh);

	printf("Shaders y cositas done.\n");
}

void onFrame() {
	ST::OpenGl::Instance().drawObj(gShaderProgram, gMesh);
}

// -----------------------------------------------------------------------------------------------------------

clock_t lastTime;

int main(){
	printf("-- Welcome to Space Turtle Engine --\n");
	
	// Window
	//ST::Window* w = new ST::Window(1090, 720);
	ST::Window w(1090, 720);
	w.Focus();

	float c[3] = {1.0f,0.8f,0.9f};


	onInit();

	
	clock_t deltaTime;
	//int MaxFPSWant = 10;
	//double MaxFPS = 1000.0f / MaxFPSWant;

	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)){
		deltaTime = clock() - lastTime;
		double fps = (1.0f / deltaTime) * 1000.0f;
		lastTime = clock();

		//printf("DeltaTime-> %d ms \n", deltaTime);
		//printf("FPS-> %f \n", fps);
		//printf("LastTime-> %d \n", lastTime);

		w.ColorBg(sin(c[0]), sin(c[1]), sin(c[2]));

		//if (deltaTime < MaxFPS) {
			if (w.isPressed(ST::ST_INPUT_UP)) {
				printf("Voy arriba!\n");
			}
			if (w.isPressed(ST::ST_INPUT_DOWN)) {
				printf("Voy abajo!\n");
			}
			if (w.isPressed(ST::ST_INPUT_RIGHT)) {
				printf("Voy derecha!\n");
			}
			if (w.isPressed(ST::ST_INPUT_LEFT)) {
				printf("Voy izquierda!\n");
			}
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


		onFrame();

		w.Render();
	}

	printf("Bye!\n");
	return 0;
}

*/
/*
int main(){

	ST::Window w(1090, 720);
	w->Focus();
	
	object triangle = createTriangle();

	while(w->isOpen()){

		if(isDown(INPUT_LEFT)){
			triangle->rotateX(1.0f);
		}
		if(isDown(INPUT_RIGHT)){
			triangle->rotateX(-1.0f);
		}

		ventana.draw(triangle);

	}

	return 0;
}
*/
/*
int main(){
	ST::Engine engine;
	w = engine.CreateWindow(1090,720);

	w->Focus();

	Triangulo tri(pos,escale,rot);

	while(w->isOpen()){

		if(engine.isDown(INPUT_LEFT)){
			tri->rotateX(1.0f);
		}
		if(engine.isDown(INPUT_RIGHT)){
			tri->rotateX(-1.0f);
		}

		ventana.draw(tri);

	}

	return 0;
}
*/

int main() {
	ST::Window w;
	w.Focus();

	ST::Triangle tri;

	while (w.isOpen()) {
		w.ColorBg(0.2f,0.2f,0.2f);

		if (w.isPressed(ST::ST_INPUT_RIGHT)) { tri.Move({ 0.3f,0.0f,0.0f }); }
		if (w.isPressed(ST::ST_INPUT_LEFT)) {tri.Move({ -0.3f,0.0f,0.0f });}
		if (w.isPressed(ST::ST_INPUT_UP)) {tri.Move({ 0.0f,0.3f,0.0f });}
		if (w.isPressed(ST::ST_INPUT_DOWN)) {tri.Move({ 0.0f,-0.3f,0.0f });}
		printf("X: %f - Y %f - Z %f\n", tri.getPosition().x, tri.getPosition().y, tri.getPosition().z);
		if (w.isPressed(ST::ST_INPUT_FIRE)) { tri.RotateY(0.4f); }

		tri.Draw();
		w.Render();
	}

	return 0;
}

