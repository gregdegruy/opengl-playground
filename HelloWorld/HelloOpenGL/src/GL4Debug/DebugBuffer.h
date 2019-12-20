#include <iostream>

#include "DebugShader.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class DebugBuffer
{
public:
	DebugBuffer();
	int run();
	void createBuffer(unsigned int& buffer, unsigned int& index_buffer);
	void bindVertex(unsigned int index_to_bind, unsigned int num_floats_per_vertex);
};

