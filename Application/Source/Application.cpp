#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include "LoadTGA.h"

#include "Scene.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene4.h"
#include "Scene5.h"
#include "SceneLight.h"
#include "SceneLight2.h"
#include "AssignmentScene.h"
#include "Scene9.h"
#include "SceneSkybox.h"
#include "SceneModel.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
Mouse mouse;
const unsigned height = 900;
const unsigned width = 1200;
bool enableMouse = true;
GLFWcursor* cursor;

//Define an error callback
static void error_callback(int error, const char* description) {
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static void mouse_callback(GLFWwindow* window, double x, double y) {
	if (x < width / 2) {
		mouse.left = true;
		mouse.right = false;
		mouse.x_diff = (width / 2) - x;
	}
	else if (x > width / 2) {
		mouse.left = false;
		mouse.right = true;
		mouse.x_diff = x - (width / 2);
	}
	if (y < height / 2) {
		mouse.up = false;
		mouse.down = true;
		mouse.y_diff = (height / 2) - y;
	}
	else if (y > height / 2) {
		mouse.up = true;
		mouse.down = false;
		mouse.y_diff = y - (height / 2);
	}
}

static void scroll_callback(GLFWwindow* window, double nan, double offSet) {
	mouse.scroll = offSet;
}

void resize_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}

bool Application::IsKeyPressed(unsigned short key) {
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application() {}

Application::~Application() {}

void Application::Init() {
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(width, height, "Week 6", NULL, NULL);
	glfwSetWindowSizeCallback(m_window, resize_callback);
	cursor = LoadCrosshair("Image//crosshai.tga");
	//If the window couldn't be created
	if (!m_window) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
}

void Application::Run() {
	//Main Loop
	Scene *scene = new SceneModel();
	scene->Init();
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE)) {
		scene->Update(m_timer.getElapsedTime(), mouse);
		scene->Render();
		if (Application::IsKeyPressed('F')) {
			glfwSetCursorPosCallback(m_window, mouse_callback);
			glfwSetScrollCallback(m_window, scroll_callback);
			glfwSetCursor(m_window, cursor);
			enableMouse = true;
		}
		if (Application::IsKeyPressed('G')) {
			enableMouse = false;
		}
		if (enableMouse) {
			glfwSetCursorPosCallback(m_window, mouse_callback);
			glfwSetScrollCallback(m_window, scroll_callback);
			glfwSetCursor(m_window, cursor);
			mouse.reset();
			glfwSetCursorPos(m_window, width / 2, height / 2);
		}
		else {
			glfwSetCursorPosCallback(m_window, NULL);
			glfwSetScrollCallback(m_window, NULL);
			glfwSetCursor(m_window, NULL);
		}
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene;
}

void Application::Exit() {
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
