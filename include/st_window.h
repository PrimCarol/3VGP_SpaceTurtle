#ifndef _SPACE_TURTLE_WINDOW_H_
#define _SPACE_TURTLE_WINDOW_H_ 1

#include <GLFW/glfw3.h>
#include <ctime>

namespace ST {

	enum ST_INPUT{
		ST_INPUT_UP,
		ST_INPUT_DOWN,
		ST_INPUT_RIGHT,
		ST_INPUT_LEFT,
		ST_INPUT_FIRE,
		ST_INPUT_JUMP,
		ST_INPUT_ESCAPE,
	};

	class Window{
	public:
		/* Contructor with default values (1080, 720) */
		Window();
		/* Constructor with witdh and height */
		Window(int width, int height);

		//GLFWwindow* GetWindow();

		void Focus() const;
		void Render();
		void Clear() const;
		
		// ------ Inputs ------
		bool isDown(ST_INPUT input);
		bool isPressed(ST_INPUT input);
		bool isUp(ST_INPUT input);
		
		// Keyboard
		//bool isKeyDown(int keyboard);
		//bool isKeyPressed(int keyboard);
		//bool isKeyReless(int keyboard);
		
		// Mouse
		double mousePosX();
		double mousePosY();
		//bool isMouseDown(int button);
		//bool isMousePressed(int button);
		//bool isMouseReless(int button);

		/* Return if window is opened */
		bool isOpen() const;

		/* Change the Background Color */
		void ColorBg(float c[4]);
		void ColorBg(float r, float g, float b, float a = 0);

		/* Delta Time */
		float DeltaTime() const;
		double FPS(const float time) const;

		~Window();

		GLFWwindow* glWindow;
	private:
		Window(const Window& o);
		float color[4];

		clock_t lastTime;
		clock_t deltaTime;

		double mouseX=0.0f, mouseY=0.0f;
		int lastKeyPressed = -1;
		int lastMousePressed = -1;
	};
}

#endif