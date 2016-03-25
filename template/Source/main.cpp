// Standard C++
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>

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
#include "../VS2013/Building.h"
#include "../VS2013/Camera.h"
#include "../VS2013/Structure.h"
#include "../VS2013/utility.h"
#include "../VS2013/Sun.h"
#include "../VS2013/Shader.h"

GLFWwindow* window = 0x00;

GLuint building_shader = 0;
GLuint block_shader = 0;

GLuint view_matrix_id = 0;
GLuint model_matrix_id = 0;
GLuint proj_matrix_id = 0;

///Transformations
glm::mat4 proj_matrix;
glm::mat4 view_matrix;
glm::mat4 model_matrix;

Camera* cameraptr;


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
	case GLFW_KEY_A:
		cameraptr->translate(-cameraptr->right() * cameraptr->movementSpeed);
		break;
	case GLFW_KEY_D:
		cameraptr->translate(cameraptr->right() * cameraptr->movementSpeed);
		break;
	case GLFW_KEY_W:
		cameraptr->translate(cameraptr->forward() * cameraptr->movementSpeed);
		break;
	case GLFW_KEY_S:
		cameraptr->translate(-cameraptr->forward() * cameraptr->movementSpeed);
		break;
	default:
		break;
	}
}

void windowResize(GLFWwindow* window, int width, int height){
	GLfloat aspectRatio = width / height;
	glViewport(0, 0, width, height);
	//from http://stackoverflow.com/questions/26831962/opengl-orthographic-projection-oy-resizing
	cameraptr->setAspectRatio(aspectRatio);
}


void cursorMoved(GLFWwindow* window, const double x, const double y)
{
	cameraptr->orientToCursor(x, y);
}


bool initialize() {
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

	glfwMakeContextCurrent(window);

	/// Initialize GLEW extension handler
	glewExperimental = GL_TRUE;	///Needed to get the latest version of OpenGL
	glewInit();

	/// Get the current OpenGL version
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
	glDisableVertexAttribArray(0);
	//Properly de-allocate all resources once they've outlived their purpose
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	// Close GL context and any other GLFW resources
	glfwTerminate();

	return true;
}


int main() {
	initialize();

	/*TEST*/
	/*
	Structure s1 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	Structure s2 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(5.0f, 0.0f, 0.0f));
	Structure s3 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(5.0f, 5.0f, 0.0f));
	Structure s4 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(0.0f, 5.0f, 0.0f));
	*/
	/*UNTEST*/

	Camera camera(*window);
	cameraptr = &camera;

	Sun sun(cameraptr);
	Sun *sunptr = &sun;

	World world;
	World* worldptr = &world;

	/*
	building buildings;
	building* buildingsptr = &buildings;
	buildingsptr->BuildCity();
	*/

	// This will identify our vertex buffer
	//GLuint vertexbuffer;

	//why does this take priority?
	//shader_program = loadShaders("../Source/BLOCK_VERTEX_SHADER.vs", "../Source/BLOCK_FRAG_SHADER.frag");
	//shader_program = loadShaders("../Source/COMP371_hw1.vs", "../Source/COMP371_hw1.fss");
	Shader building_shader("../Source/COMP371_hw1.vs", "../Source/COMP371_hw1.fss");
	Shader block_shader("../Source/BLOCK_VERTEX_SHADER.vs", "../Source/BLOCK_FRAG_SHADER.frag");
	Shader lighting_shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
	//The three variables below hold the id of each of the variables in the shader
	//If you read the vertex shader file you'll see that the same variable names are used.

	
	view_matrix_id = glGetUniformLocation(block_shader.programID(), "view_matrix");
	model_matrix_id = glGetUniformLocation(block_shader.programID(), "model_matrix");
	proj_matrix_id = glGetUniformLocation(block_shader.programID(), "proj_matrix");

	while (!glfwWindowShouldClose(window))
	{
		proj_matrix = cameraptr->projection();
		view_matrix = cameraptr->view();

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glPointSize(point_size);

		//glUseProgram(shader_program);
		//Pass the values of the three matrices to the shaders


		//building_shader.use();
		//buildingsptr->Draw();

		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));

		lighting_shader.use();
		sunptr->Draw();

		block_shader.use();
		worldptr->Draw();

		


		/*TEST*/
		/*
		glUniformMatrix4fv(Structure::projMatrixID, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		glUniformMatrix4fv(Structure::viewMatrixID, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(Structure::modelMatrixID, 1, GL_FALSE, glm::value_ptr(model_matrix));
		s1.draw();
		s2.draw();
		s3.draw();
		s4.draw();
		*/
		/*UNTEST*/

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	cleanUp();
	return 0;
}