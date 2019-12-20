#include "VertexBufferOpt.h"

VertexBufferOpt::VertexBufferOpt() {}

int VertexBufferOpt::run()
{
	GLFWwindow* window;
	if (!glfwInit()) { return -1; }
	window = glfwCreateWindow(640, 480, "Reality Display Processor", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	GLenum initResult = glewInit();
	if (GLEW_OK != initResult) {
		std::cout << "error initializing OpenGL\n";
	}

	std::cout << "Rendering...\nOpenGL version " << glGetString(GL_VERSION)
		<< "\nGLEW version " << glewGetString(GLEW_VERSION);

	unsigned int buffer;
	unsigned int index_buffer_object;
	int num_indicies = 6;
	createBuffer(buffer, index_buffer_object);	

	int vertex_index_to_bind = 0;
	int num_floats_per_vertex = 2;
	bindVertex(vertex_index_to_bind, num_floats_per_vertex);

	ShaderOpt optimized_shader;
	ShaderProgramSource source = optimized_shader
		.parseShader("res/shaders/Basic.shader"); // ensure debug working dir is relative to $(ProjectDir)

	unsigned int shader_bits = optimized_shader
		.createShader(source.VertextSource, source.FragmentSource);
	glUseProgram(shader_bits);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// glDrawArrays(GL_TRIANGLES, vertex_index_to_bind, 6);
		// use below for index buffer
		// triple AAA games use me :)
		glDrawElements(GL_TRIANGLES, num_indicies, GL_UNSIGNED_INT, nullptr); // nullptr since we bind buffers using glGenBuffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shader_bits);
	glfwTerminate();

	return 0;
}

void VertexBufferOpt::createBuffer(unsigned int& buffer, unsigned int& index_buffer)
{
	const int buffer_object_size = 12; 
	const int index_buffer_object_size = 6;
	// four different verticies and 2 duplicates
	/*float triangle_verticies[buffer_object_size] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,

		 0.5f,  0.5f,
		-0.5f,  0.5f,
		-0.5f, -0.5f
	};*/
	// uh oh same memory defined twice
	// need index buffer to reuse exisiting vertex memory instead of duplicating the middle verts and the first/last
	float triangle_verticies[buffer_object_size] = {
		-0.5f, -0.5f, // 0
		 0.5f, -0.5f, // 1
		 0.5f,  0.5f, // 2
		-0.5f,  0.5f, // 3
	};
	// :) lil index buffer 
	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);	
	glBufferData(GL_ARRAY_BUFFER,
		buffer_object_size * sizeof(float),
		triangle_verticies,
		GL_STATIC_DRAW);
	
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		index_buffer_object_size * sizeof(unsigned int),
		indicies,
		GL_STATIC_DRAW);
}

void VertexBufferOpt::bindVertex(unsigned int index_to_bind, unsigned int num_floats_per_vertex) {
	bool normalize = GL_FALSE;
	GLsizei mem_address_width = sizeof(float) * num_floats_per_vertex; // num of bytes for each verticies in memory
	glEnableVertexAttribArray(index_to_bind);
	glVertexAttribPointer(index_to_bind,
		num_floats_per_vertex,
		GL_FLOAT,
		normalize,
		mem_address_width,
		0);	
}