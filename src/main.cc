#include <stdio.h>
#include <stdlib.h>

#include <random.hpp>

#include <st_window.h>

#include <st_drawobj.h>
#include <st_node.h>

void RandomPos(ST::DrawObj obj[], int size) {
	for (int i = 0; i < size; i++){
		obj[i].setPosition({glm::linearRand(-1.0f,1.0f), glm::linearRand(-1.0f,1.0f), 1.0f});
		obj[i].setScale({ glm::linearRand(0.01f,0.3f), glm::linearRand(0.01f,0.3f), 1.0f });
	}
}

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);

	// ----------------------------------------------------------------
	srand(time(0));

	ST::DrawObj a;
	ST::Triangle geometry;
	a.setMesh(&geometry);
	a.setScale({ 0.1f, 0.1f, 0.1f });
	a.getMaterial()->setColor({1.0f, 0.7f, 0.9f});

	const int howManyObjs = 100;
	ST::DrawObj b[howManyObjs];
	ST::Circle circle;
	ST::Quad quad;
	for (int i = 0; i < howManyObjs; i++){
		int geometry = glm::linearRand(0,1);
		switch (geometry){
		case 0: b[i].setMesh(&circle); break;
		case 1: b[i].setMesh(&quad); break;
		}
		//b[i].setScale({ glm::linearRand(0.01f,0.8f), glm::linearRand(0.01f,0.8f), 1.0f });
		//b[i].setPosition({ glm::linearRand(-1.0f,1.0f), glm::linearRand(-1.0f,1.0f), 1.0f });
		b[i].getMaterial()->setColor({ glm::linearRand(0.0f,1.0f), glm::linearRand(0.0f,1.0f), glm::linearRand(0.0f,1.0f) });
	}
	RandomPos(b,howManyObjs);

	// ----------------------------------------------------------------

	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		timerForInput += w.DeltaTime();
		if (timerForInput >= 0.03f) {
			printf("Input FPS: %d \n", (int)w.FPS(timerForInput));
			if (w.isDown(ST::ST_INPUT_RIGHT)) { a.RotateZ({ -6.0f * w.DeltaTime() }); }
			if (w.isDown(ST::ST_INPUT_LEFT)) { a.RotateZ({ 6.0f * w.DeltaTime() }); }
			if (w.isDown(ST::ST_INPUT_UP)) { a.Move({ 0.0f, 10.0f * w.DeltaTime(),0.0f }); }
			if (w.isDown(ST::ST_INPUT_DOWN)) { a.Move({ 0.0f, -10.0f * w.DeltaTime(),0.0f }); }
			timerForInput = 0.0f;
		}

		// ----------------------------------------------------------------
		printf("Normal FPS: %d\n", (int)w.FPS(w.DeltaTime()));

		for (int i = 0; i < howManyObjs; i++){
			b[i].draw();
		}

		a.draw();
		
		timerForSomething += w.DeltaTime();
		if (timerForSomething >= 0.07f) {
			printf("Other FPS: %d \n", (int)w.FPS(timerForSomething));
			timerForSomething = 0.0f;
		}

		w.initImGuiWindow("Ventana Guay");
		if (w.buttonImGui("ReGenerate")) {
			RandomPos(b,howManyObjs);
		}
		w.endImGuiWindow();

		/*w.initImGuiWindow("Ventana UWU");
		w.textImGui("Adios");
		w.endImGuiWindow();*/
		// ----------------------------------------------------------------

		w.Render();	

	}

	return 0;
}

/* Main

int main{

	// Node -> EmptyObj - DrawObj

	EmptyObj Scene;

	DrawObj obj; // Como saber si es dibujable o no?
	Scene.setChild(obj);

	obj.setCustomShader(); // Que por defecto sera el basico.
	obj.setMesh(Mesh::Cube());


	while(w.Open()){


		// Camera.Render(scene);
		obj.getMesh().render();


	}

	return 0;
}


*/
