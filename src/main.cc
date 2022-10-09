#include <stdio.h>
#include <stdlib.h>

#include <st_engine.h>

#include <st_triangle.h>

// Buffers hold sound data
//ALuint buf;
// Sources are points emitting sound
//ALuint src;

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);
	
	ST::Triangle tri({ 0.0f,0.0f,0.0f }, {0.5f,0.5f,0.5f});


	// ******* TEST ********
	/*
	// Initialize OpenAL
	ALCdevice* device;
	device = alcOpenDevice(NULL);

	ALCcontext* context;
	context = alcCreateContext(device, NULL);

	// Create a source
	alGenSources(1, &src);
	if (alGetError() != AL_NO_ERROR) {
		fprintf(stderr, "Failed to create OpenAL source!\n");
		// handle errors
	}

	// Position of the source sound.
	ALfloat source_pos[] = { 0.0, 0.0, 0.0 };
	// Velocity of the source sound.
	ALfloat source_vel[] = { 0.0, 0.0, 0.0 };
	alSourcef(src, AL_PITCH, 1.0f);
	alSourcef(src, AL_GAIN, 1.0f);
	alSourcefv(src, AL_POSITION, source_pos);
	alSourcefv(src, AL_VELOCITY, source_vel);
	alSourcei(src, AL_LOOPING, 1);

	// Load wave data into a buffer
	ALsizei size = 0.0f;
	ALsizei frequency = 0.0f;
	ALenum format;
	if (ST::LoadWavFile("../others/pepe.wav", &buf, &size, &frequency, &format)) {
		fprintf(stderr, "Could not load\n");
		alDeleteSources(1, &src);
	}

	// Link source with buffer
	alSourcei(src, AL_BUFFER, buf);
	// Play source
	alSourcePlay(src);
	*/


	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		timerForInput += w.DeltaTime();
		if (timerForInput >= 0.03f) {
			printf("Input FPS: %d \n", (int)w.FPS(timerForInput));
			if (w.isDown(ST::ST_INPUT_RIGHT)) { tri.Move({ 6.0f * w.DeltaTime(),0.0f,0.0f }); }
			if (w.isDown(ST::ST_INPUT_LEFT)) { tri.Move({ -6.0f * w.DeltaTime(),0.0f,0.0f }); }
			if (w.isDown(ST::ST_INPUT_UP)) { tri.Move({ 0.0f, 6.0f * w.DeltaTime(),0.0f }); }
			if (w.isDown(ST::ST_INPUT_DOWN)) { tri.Move({ 0.0f, -6.0f * w.DeltaTime(),0.0f }); }
			timerForInput = 0.0f;
		}

		printf("Normal FPS: %d\n", (int)w.FPS(w.DeltaTime()));

		tri.Draw();
		
		timerForSomething += w.DeltaTime();
		if (timerForSomething >= 0.07f) {
			printf("Other FPS: %d \n", (int)w.FPS(timerForSomething));
			timerForSomething = 0.0f;
		}

		w.initImGuiWindow("FPS");
		w.textImGui("Holita");
		w.endImGuiWindow();

		w.Render();


		

	}

	return 0;
}

