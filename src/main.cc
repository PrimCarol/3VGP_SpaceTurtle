#include <stdio.h>
#include <stdlib.h>

#include <st_engine.h>

#include <st_triangle.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);

	ST::Triangle tri({ 0.0f,0.0f,0.0f }, {0.5f,0.5f,0.5f});

	float timerForInput = 0.0f;
	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		//timerForInput += w.DeltaTime();
		//if (timerForInput >= 0.07f) {
			//printf("Input FPS: %d \n", (int)w.FPS(timerForInput));
			if (w.isDown(ST::ST_INPUT_RIGHT)) { tri.Move({ 6.0f * w.DeltaTime(),0.0f,0.0f }); }
			if (w.isDown(ST::ST_INPUT_LEFT)) { tri.Move({ -6.0f * w.DeltaTime(),0.0f,0.0f }); }
			if (w.isDown(ST::ST_INPUT_UP)) { tri.Move({ 0.0f, 6.0f * w.DeltaTime(),0.0f }); }
			if (w.isDown(ST::ST_INPUT_DOWN)) { tri.Move({ 0.0f, -6.0f * w.DeltaTime(),0.0f }); }
			//timerForInput = 0.0f;
		//}

		//printf("Normal FPS: %d\n", (int)w.FPS(w.DeltaTime()));

		tri.Draw();

		w.Render();
	}

	return 0;
}

