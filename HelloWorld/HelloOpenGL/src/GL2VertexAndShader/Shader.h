#include <iostream>
#include <string>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class Shader
{
public:
	Shader();
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertextShader, const std::string& fragmentShader);
};