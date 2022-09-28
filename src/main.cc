#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <st_window.h>

int main(){
	printf("-- Welcome to Space Turtle --\n");
	
	// Window
	ST::Window* w = new ST::Window(1090, 720);
	w->Focus();

	float c[3] = {1.0f,0.8f,0.9f};

	while (w->isOpen()){
		
		w->ColorBg(sin(c[0]), sin(c[1]), sin(c[2]));

		//if (w->isKeyDown(GLFW_KEY_J)) {
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

		w->Render();
	}

	delete w;

	printf("Bye!\n");
	return 0;
}