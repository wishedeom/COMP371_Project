#include "Shader.h"
#include "glew.h"
#include "glfw3.h"
#include <vector>


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	: m_programID(makeShaderProgram(vertexPath, fragmentPath))
	, m_initialized(true) {}


Shader::Shader()
	: m_initialized(false) {}


GLuint Shader::programID() const { return m_programID; }


void Shader::use() const { glUseProgram(m_programID); }


std::string Shader::readSourceCode(const std::string& path)
{
	// To store source code
	std::string sourceCode;

	std::ifstream stream(path, std::ios::in);
	if (stream.is_open())
	{
		std::string line;
		while (getline(stream, line))
		{
			sourceCode += line + "\n";
		}
		stream.close();
	}
	else
	{
		std::cout << "Error opening " << path << "." << std::endl;
	}
	return sourceCode;
}


GLuint Shader::compileShader(const std::string& path, const GLenum shaderType)
{
	// Create shader, store id
	const GLuint id = glCreateShader(shaderType);

	const std::string sourceCode = readSourceCode(path);
	std::cout << "Compiling shader " << path;

	// Compilation
	char const *p_sourceCode = sourceCode.data();
	glShaderSource(id, 1, &p_sourceCode, nullptr);
	glCompileShader(id);

	// Check compilation result
	GLint result = GL_FALSE;
	int infoLogLength;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetShaderInfoLog(id, infoLogLength, nullptr, &errorMsg[0]);
		printf("%s\n", &errorMsg[0]);
	}

	return id;
}


GLuint Shader::makeShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	const auto vertexShaderID = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	const auto fragmentShaderID = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	std::cout << "Linking shader program." << std::endl;

	// Create program
	GLuint programID = glCreateProgram();

	// Attach shaders
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	// Bind inputs
	glBindAttribLocation(programID, 0, "in_Position");
	glBindAttribLocation(programID, 1, "in_Color");

	// Link program
	glLinkProgram(programID);

	// Check the program
	GLint result = GL_FALSE;
	int infoLogLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> errmsg(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, nullptr, &errmsg[0]);
		printf("%s\n", &errmsg[0]);
	}

	// Delete shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}


bool Shader::isInitialized() const { return m_initialized; }


GLuint Shader::projViewMatrixID() const { return glGetUniformLocation(m_programID, "projViewMatrix"); }