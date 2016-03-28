#pragma once
#include "glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{

	// Reads shader ource code from a file.
	// path: The file path of the shader source code, written in GLSL.
	// Returns: The shader source code, as a string.
	static std::string readSourceCode(const std::string& path);


	// Compiles a shader program from a file.
	// path: The file path of the shader source code, written in GLSL.
	// shaderType: Either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
	// Returns: The OpenGL ID of the shader.
	static GLuint compileShader(const std::string& path, const GLenum shaderType);


	// Reads, compiles, and links a vertex and fragment shader, then attaches them to a shader program.
	// vertexShaderPath: The file path of the vertex shader source code, written in GLSL.
	// fragmentShaderPath: The file path of the vertex shader source code, written in GLSL.
	// Returns: The OpenGL ID of the shader program.
	static GLuint makeShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);


	GLuint m_programID;		// Holds the OpenGL shader program ID.
	bool m_initialized;		// Has the shader program been created yet?

public: 

    // Constructor generates the shader on the fly
	// vertexPath: Path name for vertex shader souce code.
	// fragmentPath: Path name for fragment shader souce code.
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	

	// Constructs an uninitialized Shader.
	Shader();

	// Returns the program ID of the shader program.
	GLuint programID() const;

	
	// Returns true if and only if the shader program has been created.
	bool initialized() const;


    // Uses the current shader
	void use() const;

};