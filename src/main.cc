#include <stdio.h>
#include <stdlib.h>


#include <st_engine.h>

#include <st_triangle.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);
	
	ST::Triangle tri({ 0.0f,0.0f,0.0f }, {0.1f,0.1f,0.1f});

	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		timerForInput += w.DeltaTime();
		if (timerForInput >= 0.03f) {
			printf("Input FPS: %d \n", (int)w.FPS(timerForInput));
			if (w.isDown(ST::ST_INPUT_RIGHT)) { tri.RotateZ({ -6.0f * w.DeltaTime()}); }
			if (w.isDown(ST::ST_INPUT_LEFT)) { tri.RotateZ({ 6.0f * w.DeltaTime()}); }
			if (w.isDown(ST::ST_INPUT_UP)) { tri.Move({ 0.0f, 10.0f * w.DeltaTime(),0.0f }); }
			if (w.isDown(ST::ST_INPUT_DOWN)) { tri.Move({ 0.0f, -10.0f * w.DeltaTime(),0.0f }); }
			timerForInput = 0.0f;
		}

		printf("Normal FPS: %d\n", (int)w.FPS(w.DeltaTime()));

		tri.Draw();
		
		timerForSomething += w.DeltaTime();
		if (timerForSomething >= 0.07f) {
			printf("Other FPS: %d \n", (int)w.FPS(timerForSomething));
			timerForSomething = 0.0f;
		}

		w.initImGuiWindow("Ventana Guay");
		w.textImGui("Holita");
		w.endImGuiWindow();

		w.initImGuiWindow("Ventana UWU");
		w.textImGui("Adios");
		w.endImGuiWindow();

		w.Render();


		

	}

	return 0;
}

