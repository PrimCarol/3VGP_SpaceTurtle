#include <stdio.h>
#include <stdlib.h>


//#include <st_engine.h>
#include <st_window.h>

#include <st_drawobj.h>
#include <st_node.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);


	ST::DrawObj a;
	ST::Circle geometry;
	a.setMesh(&geometry);
	a.Scale({0.1f, 0.1f, 0.1f});
	//ST::Program basicProgram;
	//a.setMaterial(basicProgram);

	ST::DrawObj b;
	ST::Circle geometry_2;
	b.setMesh(&geometry_2);
	b.Scale({ 0.1f, 0.1f, 0.1f });

	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		timerForInput += w.DeltaTime();
		if (timerForInput >= 0.03f) {
			printf("Input FPS: %d \n", (int)w.FPS(timerForInput));
			//if (w.isDown(ST::ST_INPUT_RIGHT)) { tri.RotateZ({ -6.0f * w.DeltaTime()}); }
			//if (w.isDown(ST::ST_INPUT_LEFT)) { tri.RotateZ({ 6.0f * w.DeltaTime()}); }
			//if (w.isDown(ST::ST_INPUT_UP)) { tri.Move({ 0.0f, 10.0f * w.DeltaTime(),0.0f }); }
			//if (w.isDown(ST::ST_INPUT_DOWN)) { tri.Move({ 0.0f, -10.0f * w.DeltaTime(),0.0f }); }
			if (w.isDown(ST::ST_INPUT_RIGHT)) { a.RotateZ({ -6.0f * w.DeltaTime() }); }
			if (w.isDown(ST::ST_INPUT_LEFT)) { a.RotateZ({ 6.0f * w.DeltaTime() }); }
			if (w.isDown(ST::ST_INPUT_UP)) { a.Move({ 0.0f, 10.0f * w.DeltaTime(),0.0f }); }
			if (w.isDown(ST::ST_INPUT_DOWN)) { a.Move({ 0.0f, -10.0f * w.DeltaTime(),0.0f }); }
			//printf("Position -> X: %f - Y: %f - Z: %f\n", a.getPosition().x, a.getPosition().y, a.getPosition().z);
			timerForInput = 0.0f;
		}

		printf("Normal FPS: %d\n", (int)w.FPS(w.DeltaTime()));

		a.draw();
		b.draw();
		
		timerForSomething += w.DeltaTime();
		if (timerForSomething >= 0.07f) {
			printf("Other FPS: %d \n", (int)w.FPS(timerForSomething));
			timerForSomething = 0.0f;
		}

		/*w.initImGuiWindow("Ventana Guay");
		w.textImGui("Holita");
		w.endImGuiWindow();

		w.initImGuiWindow("Ventana UWU");
		w.textImGui("Adios");
		w.endImGuiWindow();*/

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
