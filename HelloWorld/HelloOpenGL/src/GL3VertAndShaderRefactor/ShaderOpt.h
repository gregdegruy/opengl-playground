#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

struct ShaderProgramSource
{
	std::string VertextSource;
	std::string FragmentSource;
};

class ShaderOpt
{
public:
	ShaderOpt();
	ShaderProgramSource parseShader(const std::string& filePath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertextShader, const std::string& fragmentShader);
};