#include <iostream>

#include "UniformShader.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class UniformBuffer
{
public:
	UniformBuffer();
	int run();
	void createBuffer(unsigned int& buffer, unsigned int& index_buffer);
	void bindVertex(unsigned int index_to_bind, unsigned int num_floats_per_vertex);
};

