#define GLEW_STATIC

// Standard C++
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>	
#include <ctime>
#include <memory>

// Standard C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Third-party
#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

// Project
#include "../VS2013/Block.h"
#include "../VS2013/World.h"
#include "../VS2013/Camera.h"
#include "../VS2013/Drawable.h"
#include "../VS2013/utility.h"
#include "../VS2013/PlayerController.h"

GLFWwindow* window = 0x00;

///Transformations
glm::mat4 proj_matrix;
glm::mat4 view_matrix;


std::unique_ptr<PlayerController> playerController;


//GLuint VBO, VAO, EBO;

GLfloat point_size = 3.0f;

///Handle the keyboard input
void keyPressed(GLFWwindow *_window, const int key, const int scancode, const int action, const int mods) {
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	case GLFW_KEY_W:
		if (action == GLFW_PRESS)
		{
			playerController->moveForward();
		}
		else if (action == GLFW_RELEASE)
		{
			playerController->stopAxial();
		}
		break;
	case GLFW_KEY_S:
		if (action == GLFW_PRESS)
		{
			playerController->moveBackward();
		}
		else if (action == GLFW_RELEASE)
		{
			playerController->stopAxial();
		}
		break;
	case GLFW_KEY_D:
		if (action == GLFW_PRESS)
		{
			playerController->moveRight();
		}
		else if (action == GLFW_RELEASE)
		{
			playerController->stopLateral();
		}
		break;
	case GLFW_KEY_A:
		if (action == GLFW_PRESS)
		{
			playerController->moveLeft();
		}
		else if (action == GLFW_RELEASE)
		{
			playerController->stopLateral();
		}
		break;
	default:
		break;
	}
}

void windowResize(GLFWwindow* window, int width, int height){
	GLfloat aspectRatio = width / height;
	glViewport(0, 0, width, height);
	//from http://stackoverflow.com/questions/26831962/opengl-orthographic-projection-oy-resizing
	playerController->camera().setAspectRatio(aspectRatio);
}


void cursorMoved(GLFWwindow* window, const double x, const double y)
{
	playerController->camera().orientToCursor(x, y);
}


bool initialize()
{
	std::srand(std::time(0));

	/// Initialize GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	/// Create a window of size 640x480 and with title "Lecture 2: First Triangle"
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	window = glfwCreateWindow(800, 800, "COMP371: Team 8 Project", nullptr, nullptr);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	///Register the keyboard callback function: keyPressed(...)
	glfwSetWindowSizeCallback(window, windowResize);
	glfwSetKeyCallback(window, keyPressed);
	glfwSetCursorPosCallback(window, cursorMoved);

	// Hides the mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwMakeContextCurrent(window);

	/// Initialize GLEW extension handler
	glewExperimental = GL_TRUE;	///Needed to get the latest version of OpenGL
	glewInit();

	/// Get the current Open	GL version
	const GLubyte* renderer = glGetString(GL_RENDERER); /// Get renderer string
	const GLubyte* version = glGetString(GL_VERSION); /// Version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/// Enable the depth test i.e. draw a pixel if it's closer to the viewer
	glEnable(GL_DEPTH_TEST); /// Enable depth-testing
	glDepthFunc(GL_LESS);	/// The type of testing i.e. a smaller value as "closer"

	return true;
}

bool cleanUp() {
	glfwTerminate();
	return true;
}


int main()
{
	initialize();

	Camera camera(*window);
	playerController = std::make_unique<PlayerController>(camera);
	
	DirectionalLight light(camera);

	World world(5, 5);

	while (!glfwWindowShouldClose(window))
	{

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glPointSize(point_size);

		world.draw(camera, light);

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		playerController->update();
	}

	cleanUp();
	return 0;
}