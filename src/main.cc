#include <stdio.h>
#include <stdlib.h>

#include <st_engine.h>

#include <st_triangle.h>

float timerForInput = 0;

int main() {
	ST::Window w;
	
	ST::Triangle tri;

	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.ColorBg(0.2f,0.2f,0.2f);

		timerForInput += w.DeltaTime();
		if (timerForInput >= 0.1f) {
			printf("Compruebo el Input\n");
			if (w.isPressed(ST::ST_INPUT_RIGHT)) { tri.Move({ 6.0f * w.DeltaTime(),0.0f,0.0f }); }
			if (w.isPressed(ST::ST_INPUT_LEFT)) { tri.Move({ -6.0f * w.DeltaTime(),0.0f,0.0f }); }
			if (w.isPressed(ST::ST_INPUT_UP)) { tri.Move({ 0.0f, 6.0f * w.DeltaTime(),0.0f }); }
			if (w.isPressed(ST::ST_INPUT_DOWN)) { tri.Move({ 0.0f, -6.0f * w.DeltaTime(),0.0f }); }
			timerForInput = 0;
		}
		if (tri.getPosition().x > 1.0f) {
			tri.Move({-4.0f,0.0f,0.0f});
		}

		tri.Draw();
		w.Render();
	}

	return 0;
}

