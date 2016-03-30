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

GLFWwindow* window = 0x00;

GLuint building_shader = 0;
GLuint block_shader = 0;

GLuint view_matrix_id = 0;
GLuint model_matrix_id = 0;
GLuint proj_matrix_id = 0;
GLuint model_view_matrix_id = 0;


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
	GLfloat aspectRatio = (GLfloat)width / (GLfloat) height;
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
	/*	Structure s1 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	Structure s2 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(5.0f, 0.0f, 0.0f));
	Structure s3 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(5.0f, 5.0f, 0.0f));
	Structure s4 = Structure::randomStructure(15, 3.0f, 100.0f, glm::vec3(0.0f, 5.0f, 0.0f));
	*/	/*UNTEST*/

	Camera camera(*window);
	cameraptr = &camera;

	World world;
	World* worldptr = &world;
	Tree* treeptr = new Tree(0.25f, 0.375f, "C:/Users/mimi/Desktop/template/MegaOne/Images/tree2.png");
	building buildings;
	building* buildingsptr = &buildings;
	buildingsptr->BuildCity();
	// This will identify our vertex buffer
	GLuint vertexbuffer;

	/* TREE POSITION TEST */
	glm::vec3 pos[] = {
		glm::vec3(0.0f, 0.0f, 0.0f)/*,
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f, 0.5f, 0.0f)*/
	};

	/* END OF TREE POSITION TEST */

	//why does this take priority?
	//shader_program = loadShaders("../Source/BLOCK_VERTEX_SHADER.vs", "../Source/BLOCK_FRAG_SHADER.frag");
	//shader_program = loadShaders("../Source/COMP371_hw1.vs", "../Source/COMP371_hw1.fss");
	Shader building_shader("../Source/COMP371_hw1.vs", "../Source/COMP371_hw1.fss");
	Shader block_shader("../Source/BLOCK_VERTEX_SHADER.vs", "../Source/BLOCK_FRAG_SHADER.frag");
	Shader tree_shader("../Source/TREE_VERTEX_SHADER.vs", "../Source/TREE_FRAG_SHADER.frag");
	//The three variables below hold the id of each of the variables in the shader
	//If you read the vertex shader file you'll see that the same variable names are used.
	while (!glfwWindowShouldClose(window))
	{

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glPointSize(point_size);

		//Pass the values of the three matrices to the shaders
		
		///Transformations
		glm::mat4 proj_matrix;
		glm::mat4 view_matrix;
		glm::mat4 model_matrix;
	//	glm::mat4 model_view_matrix;

		view_matrix_id = glGetUniformLocation(tree_shader.programID(), "view_matrix");
		model_matrix_id = glGetUniformLocation(tree_shader.programID(), "model_matrix");
	//	model_view_matrix_id = glGetUniformLocation(tree_shader.programID(), "model_view_matrix");
		proj_matrix_id = glGetUniformLocation(tree_shader.programID(), "proj_matrix");


		/* Method #5: With the assumption that the billboard is parallel to xz-plane */

		view_matrix = cameraptr->view();
		glm::vec3 camRight = glm::normalize(glm::vec3(view_matrix[0][0], view_matrix[0][1], view_matrix[0][2]));
		glm::vec3 camUp = glm::normalize(glm::vec3(view_matrix[1][0], view_matrix[1][1], view_matrix[1][2]));
		//glm::vec3 camRight = cameraptr->right();
		//glm::vec3 camUp = glm::cross(cameraptr->forward(), camRight);
		glm::vec3 camPos = cameraptr->position();

		glm::vec3 billFront = camPos - pos[0];
		glm::vec3 billFrontNorm = glm::normalize(billFront);
		glm::vec3 billRight = glm::normalize(glm::cross(camUp, billFront));
		glm::vec3 billUp = glm::normalize(glm::cross(billFront, billRight));

		// Place the tree in the world
		model_matrix = glm::translate(model_matrix, pos[0]);

		// Temporarily move the tree to the camera
//		model_matrix = glm::translate(model_matrix, billFront);

		// Find the rotation angle
		GLfloat dot = glm::dot(camRight, billRight);
		GLfloat camRightMag = glm::length(camRight);
		GLfloat billRightMag = glm::length(billRight);
		GLfloat angle = glm::acos(dot / (camRightMag * billRightMag));

		// Perform the rotation
		glm::vec3 rotAxis = glm::vec3(camUp.x, camUp.y, 1.0);
//		model_matrix = glm::rotate(model_matrix, angle, camUp);

		// Move the tree back
//		model_matrix = glm::translate(model_matrix, glm::vec3(billFront.x * -1, billFront.y * -1, billFront.z * -1));

		//model_matrix = model_matrix * billTrans;
		proj_matrix = cameraptr->projection();
		
		
		/* Method #4 */
	/*	view_matrix = cameraptr->view();
		glm::vec3 camRight = glm::vec3(view_matrix[0][0], view_matrix[0][1], view_matrix[0][2]);
		glm::vec3 camUp = glm::vec3(view_matrix[1][0], view_matrix[1][1], view_matrix[1][2]);
		glm::vec3 camPos = cameraptr->position();
		
		glm::vec3 billFront = glm::normalize(camPos - pos[0]);
		glm::vec3 billRight = glm::normalize(glm::cross(camUp, billFront));
		glm::vec3 billUp = glm::normalize(glm::cross(billFront, billRight));
		glm::mat4 billTrans; // r1: Right, r2: Up, r3: Front, c4: billPos
		billTrans[0][0] = billRight.x; // Right
		billTrans[0][1] = billRight.y;
		billTrans[0][2] = billRight.z;
		billTrans[1][0] = billUp.x; // Up
		billTrans[1][1] = billUp.y;
		billTrans[1][2] = billUp.z;
		billTrans[2][0] = billFront.x; // Front
		billTrans[2][1] = billFront.y;
		billTrans[2][2] = billFront.z;
		billTrans[0][3] = pos[0].x; // Pos
		billTrans[1][3] = pos[0].y;
		billTrans[2][3] = pos[0].z;
		billTrans[3][0] = 0; // Zero
		billTrans[3][1] = 0;
		billTrans[3][2] = 0;
		billTrans[3][2] = 0;


		model_matrix = glm::translate(model_matrix, pos[0]);
		model_matrix = model_matrix * billTrans;
		proj_matrix = cameraptr->projection();
		
		*/
		/* End of Method #4 */


		/* Method #3 */
	/*	glm::vec3 treeToCam = cameraptr->position() - pos[0];
		treeToCam.y = 0.0f;
		treeToCam = glm::normalize(treeToCam);

		cameraptr->orientation.x = 0;
		cameraptr->orientation.y = 0;
		cameraptr->orientation.z = 1;
		cameraptr->orientation = glm::normalize(cameraptr->orientation());

		glm::vec3 cross = glm::cross(cameraptr->orientation(), treeToCam);

		GLfloat ang = glm::dot(cameraptr->orientation(), treeToCam);

		if (ang < 0.99990 && ang > -0.9999)
		{
			cout << "!!! BILLBOARD ROTATE  !!!" << endl;
			model_matrix = glm::rotate(model_matrix, (GLfloat)(glm::acos(ang) * 180 / pi), cross);
		}

		proj_matrix = cameraptr->projection();
		view_matrix = cameraptr->view();
*/
		/* End of Method #3 */

	//	model_view_matrix = view_matrix * model_matrix;

		
	/*	model_view_matrix = view_matrix * model_matrix;

		model_view_matrix[0][0] = 1;
		model_view_matrix[0][1] = 0;
		model_view_matrix[0][2] = 0;

		model_view_matrix[2][0] = 0;
		model_view_matrix[2][1] = 0;
		model_view_matrix[2][2] = 1;
*/
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
//		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

		block_shader.use();
		treeptr->draw();

		/*TEST*/
		/*	glUniformMatrix4fv(Structure::projMatrixID, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		glUniformMatrix4fv(Structure::viewMatrixID, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(Structure::modelMatrixID, 1, GL_FALSE, glm::value_ptr(model_matrix));
		s1.draw();
		s2.draw();
		s3.draw();
		s4.draw();
		*/	/*UNTEST*/

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	cleanUp();
	return 0;
}