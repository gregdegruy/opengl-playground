#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

struct ShaderVertexArrayProgramSource
{
	std::string VertextSource;
	std::string FragmentSource;
};

class ShaderVertexArray
{
public:
	ShaderVertexArray();
	ShaderVertexArrayProgramSource parseShader(const std::string& filePath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertextShader, const std::string& fragmentShader);
};