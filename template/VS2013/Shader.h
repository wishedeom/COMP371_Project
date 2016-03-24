#pragma once

#include "glew.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{

	GLuint m_programID;

	void checkCompileErrors(GLuint shader, std::string type);

public: 

    // Constructor generates the shader on the fly
	// vertexPath: Path name for vertex shader souce code.
	// fragmentPath: Path name for fragment shader souce code.
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	

	// Returns the program ID of the shader program
	GLuint programID() const;


    // Uses the current shader
	void Use() const;

};