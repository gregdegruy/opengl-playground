#include <iostream>

#include "Shader.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class VertexBufferAndShader
{
public:
	VertexBufferAndShader();
	int run();
	void createBuffer(unsigned int& buffer);
};
