//-------------------------------------------------------------------------------------------------------------------------
//
//													COMP 371  -  COMPUTER GRAPHICS
//
//														CONCORDIA UNIVERSITY
//															TERM PROJECT
//														    MEGA-CITY ONE
//
//
//																Authors:
//															   Andy Chen
//															  Michael Deom
//															 Adrian Gabriel
//															 Sylvie Truong
//
//
//																PRESENTED
//															April 7th, 2016
//																	to
//														   Prof. Sudhir Mudur
//																	and
//														Prof. Charalambos Poullis
//
//-------------------------------------------------------------------------------------------------------------------------

// Static linking to GLEW
#define GLEW_STATIC

															// - INCLUDES - //

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


															// - GLOBAL VARIABLES - //

// A pointer to the OpenGL window
GLFWwindow* window = 0x00;

// Manages the player's movement in the world
std::unique_ptr<PlayerController> playerController;

// Determines the size of each point drawn by OpenGL
const GLfloat pointSize = 3.0f;

// Background colour of world
const glm::vec4 clearColour(1.0f, 0.0f, 1.0f, 1.0f); // Mauve

// Size of the world, in blocks
const int worldSize = 5;


														  // - FUNCTION DECLARATIONS - //

void keyPressed(GLFWwindow *_window, const int key, const int scancode, const int action, const int mods);
void windowResize(GLFWwindow* window, int width, int height);
void cursorMoved(GLFWwindow* window, const double x, const double y);
bool initialize();
bool cleanUp();


																	// - MAIN - //

int main()
{
	// Set up OpenGL
	initialize();

	// Create a camera displaying to the window
	Camera camera(*window);

	// Initialize the player controller for user input
	playerController = std::make_unique<PlayerController>(camera);

	// Create the "sun"
	DirectionalLight light(camera);

	// Create the city
	World world(worldSize, worldSize);

	// Main game loop
	while (!glfwWindowShouldClose(window))
	{

		// Wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(clearColour.r, clearColour.g, clearColour.b, clearColour.a);
		glPointSize(pointSize);

		// Draw everything
		world.draw(camera, light);

		// Update other events like input handling
		glfwPollEvents();
		playerController->update();

		// Put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	// End program
	cleanUp();
	return 0;
}


															// - GLOBAL FUNCTIONS - //


// Handles keyboard input
void keyPressed(GLFWwindow *_window, const int key, const int scancode, const int action, const int mods)
{
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
	case GLFW_KEY_LEFT_SHIFT:
		if (action == GLFW_PRESS)
		{
			playerController->setRunning(true);
		}
		else if (action == GLFW_RELEASE)
		{
			playerController->setRunning(false);
		}
		break;
	case GLFW_KEY_SPACE:
		playerController->jump();
		break;
	default:
		break;
	}
}


// Handles window resizing
void windowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	//from http://stackoverflow.com/questions/26831962/opengl-orthographic-projection-oy-resizing
	if (height != 0)
	{
		playerController->camera().setAspectRatio(width / height);
	}
}


// Handles mouse input
void cursorMoved(GLFWwindow* window, const double x, const double y)
{
	playerController->camera().orientToCursor(x, y);
}


// Manages OpenGL set-up
bool initialize()
{
	// Seed the random number generator. Used to generate the random buildings.
	std::srand(std::time(0));

	// Initialize GL context and OS window using the GLFW helper library
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	// Create the window and set it to full-screen
	window = glfwCreateWindow(1600, 900, "COMP371: Mega-City One", glfwGetPrimaryMonitor(), nullptr);
	
	// Check for errors
	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	///Register the callback functions
	glfwSetWindowSizeCallback(window, windowResize);
	glfwSetKeyCallback(window, keyPressed);
	glfwSetCursorPosCallback(window, cursorMoved);

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	// Hides the mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Bring window into focus
	glfwMakeContextCurrent(window);

	// Initialize GLEW extension handler
	glewExperimental = GL_TRUE;		//Needed to get the latest version of OpenGL
	glewInit();

	// Get the current OpenGL version
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << std::endl;

	// Enable the depth test i.e. draw a pixel if it's closer to the viewer
	glEnable(GL_DEPTH_TEST);	// Enable depth-testing
	glDepthFunc(GL_LESS);		// The type of testing i.e. a smaller value as "closer"

	return true;
}


// Terminates OpenGL
bool cleanUp()
{
	glfwTerminate();
	return true;
}