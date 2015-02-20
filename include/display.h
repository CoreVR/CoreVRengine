#ifndef DISPLAY_H
#define DISPLAY_H

#include <GLFW/glfw3.h>
#include "camera.h"

class Display
{
	public:
		Display(int width, int height, const char* title);
		~Display();
		void Update();
		void MakeNewCameraMatrices();
		GLFWwindow* window;
		Camera camera;
		bool camMoved;
		vec3 moveVector;
	private:
		float currentTime;
		float previousTime;
		float elapsedTime;

		int windowWidth;
		int windowHeight;
		bool windowIsFullScreen;
		static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};		
#endif