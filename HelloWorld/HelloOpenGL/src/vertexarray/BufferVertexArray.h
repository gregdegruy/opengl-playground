#include <iostream>

#include "ShaderVertexArray.h"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class BufferVertexArray
{
public:
	BufferVertexArray();
	int run();
	void createBuffer(unsigned int& buffer, unsigned int& index_buffer, unsigned int& vertex_array_object);
	void bindVertex(unsigned int index_to_bind, unsigned int num_floats_per_vertex);
};

