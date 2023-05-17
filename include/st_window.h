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
		ST_INPUT_FIRE_SECOND,
		ST_INPUT_JUMP,
		ST_INPUT_SHIFT,
		ST_INPUT_ESCAPE,
		ST_INPUT_DELETE,
	};

	class Window{
	public:
		/* Contructor with default values (1080, 720) */
		Window();
		/* Constructor with witdh and height */
		Window(int width, int height);

		// ------ Basics ------
		void Focus() const;
		void Render();
		void Clear() const;

		int getWindowsHeight() const;
		int getWindowsWidth() const;

		// ------ Inputs ------
		bool inputPressed(ST_INPUT input);
		bool inputReleased(ST_INPUT input);
		bool inputPressed(const char key);
		bool inputReleased(const char key);
				
		// Mouse
		double mousePosX() const;
		double mousePosY() const;
		double mouseWheelX() const;
		double mouseWheelY() const;

		/* Return if window is opened */
		bool isOpen() const;

		/* Change the Background Color */
		void ColorBg(float c[4]);
		void ColorBg(float r, float g, float b, float a = 0);

		// ------ Delta Time ------
		float DeltaTime() const;
		double FPS(const float time) const;

		~Window();

		GLFWwindow* glWindow;
	private:
		Window(const Window& o);
		float color[4];

		clock_t lastTime;
		clock_t deltaTime;

		int window_Width_, window_Height_;
		double mouseX = 0.0f, mouseY = 0.0f;
		double mouseWheelX_ = 0.0f, mouseWheelY_ = 0.0f;
		static void scroll_callback(GLFWwindow* w, double x, double y);
		void scroll_callback(double x, double y);
		
		void setImGuiTheme();
	};
}

#endif