#ifndef _SPACE_TURTLE_WINDOW_H_
#define _SPACE_TURTLE_WINDOW_H_ 1

#include <GLFW/glfw3.h>

namespace ST {

	//enum ST_INPUT{
	//	ST_INPUT_NONE = -1,
	//	ST_INPUT_KEY_UP = GLFW_KEY_W | GLFW_KEY_UP,
	//	ST_INPUT_KEY_DOWN = GLFW_KEY_S | GLFW_KEY_DOWN,
	//	ST_INPUT_KEY_RIGHT = GLFW_KEY_D | GLFW_KEY_RIGHT,
	//	ST_INPUT_KEY_LEFT = GLFW_KEY_A | GLFW_KEY_LEFT
	//};

	class Window{
	public:
		/* Contructor with default values (1080, 720) */
		Window();
		/* Constructor with witdh and height */
		Window(int width, int height);

		//GLFWwindow* GetWindow();

		void Focus();
		void Render();
		
		// ------ Inputs ------
		//bool isInputDown(ST_INPUT input);
		//bool isInputPressed(ST_INPUT input);
		//bool isInputReless(ST_INPUT input);
		
		// Keyboard
		bool isKeyDown(int keyboard);
		bool isKeyPressed(int keyboard);
		bool isKeyReless(int keyboard);
		
		// Mouse
		double mousePosX();
		double mousePosY();
		bool isMouseDown(int button);
		bool isMousePressed(int button);
		bool isMouseReless(int button);

		/* Return if window is opened */
		bool isOpen();

		/* Change the Background Color */
		void ColorBg(float c[4]);
		void ColorBg(float r, float g, float b, float a = 0);

		~Window();

		GLFWwindow* glWindow;
	private:
		Window(const Window& o);
		float color[4];

		double mouseX=0.0f, mouseY=0.0f;
		//ST_INPUT lastInput = ST_INPUT_NONE;
		int lastKeyPressed = -1;
		int lastMousePressed = -1;
	};
}

#endif