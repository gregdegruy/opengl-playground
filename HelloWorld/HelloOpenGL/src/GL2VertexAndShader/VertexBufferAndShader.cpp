#include "VertexBufferAndShader.h"

VertexBufferAndShader::VertexBufferAndShader() {}

int VertexBufferAndShader::run()
{
	GLFWwindow* window;
	if (!glfwInit()) { return -1;  }
	window = glfwCreateWindow(640, 480, "Paper Mario", NULL, NULL);
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
	// createBuffer(buffer);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	const int buffer_object_size = 6;
	float triangle_verticies[buffer_object_size] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};
	glBufferData(GL_ARRAY_BUFFER,
		buffer_object_size * sizeof(float),
		triangle_verticies,
		GL_STATIC_DRAW);

	int vertex_index_to_bind = 0; 
	int num_floats_per_vertex = 2;
	bool normalize = GL_FALSE;
	GLsizei mem_address_width = sizeof(float) * num_floats_per_vertex; // num of bytes for each verticies in memory
	glEnableVertexAttribArray(vertex_index_to_bind); 	
	glVertexAttribPointer(vertex_index_to_bind,
		num_floats_per_vertex, 
		GL_FLOAT, 
		normalize, 
		mem_address_width, 
		0); 
	// 0 for pointer since vertext data is just -0.5f, -0.5f 
	// if had a texture coordinate in vertex pointer would be 8 bytes instead here -0.5f, -0.5f, 0.5f	
	// using glsl, opengl shader language, version 330, core no deprecared functions
	// but had to change from 330 to 410
	/*
		Rendering...
		GL version 4.6.0 NVIDIA 388.13
		GLEW version 2.1.0
		ERROR Shader::compileShader for type vertexshader
		0(3) : error C7548: 'layout(location)' requires "#extension GL_ARB_separate_shader_objects : enable" before use
		0(3) : error C0000: ... or #version 410
	*/
	std::string vertexShader = 
		"#version 410 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n" // access the glVertexAttribPointer vertext_index 0 and floats_per_vertex
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n" // requires a vec4 even though we're using a vec2, opengl does the casting/conversion for us
		"}";

	std::string fragmentShader =
		"#version 410 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n" // access the glVertexAttribPointer vertext_index 0 and floats_per_vertex
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(0.0, 0.0, 0.64, 1.0);\n" // rgba generally, HDR has larger range
		"}";
	
	Shader shader;
	unsigned int shader_bits = shader.createShader(vertexShader, fragmentShader);
	glUseProgram(shader_bits);
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, vertex_index_to_bind, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shader_bits);
	glfwTerminate();

	return 0;
}

void VertexBufferAndShader::createBuffer(unsigned int& buffer)
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	const int buffer_object_size = 6;
	float triangle_verticies[buffer_object_size] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};
	glBufferData(GL_ARRAY_BUFFER, 
		buffer_object_size * sizeof(float), 
		triangle_verticies, 
		GL_STATIC_DRAW);
}
