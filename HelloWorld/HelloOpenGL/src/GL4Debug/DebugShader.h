#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

struct DebugShaderProgramSource
{
	std::string VertextSource;
	std::string FragmentSource;
};

class DebugShader
{
public:
	DebugShader();
	DebugShaderProgramSource parseShader(const std::string& filePath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertextShader, const std::string& fragmentShader);
};