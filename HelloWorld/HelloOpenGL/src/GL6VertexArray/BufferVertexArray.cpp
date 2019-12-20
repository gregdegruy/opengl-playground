#include "BufferVertexArray.h"
#include "..\GL4Debug\HelloDebugger.h"

HelloDebugger helloDebuggerVertexArray;
											// __FILE__ is not instrinsic and most comilers should support
#define ASSERT(x) if (!(x)) __debugbreak(); // this is an instrinsic MSVC compiler function, other compilers like gcc or clang can't use this
#define GLCall(x) helloDebuggerVertexArray.GLClearError();\
	x;\
	ASSERT(helloDebuggerVertexArray.GlLogCall(#x, __FILE__, __LINE__))

// #x tells out macro x is an int

BufferVertexArray::BufferVertexArray() {}

int BufferVertexArray::run()
{
	GLFWwindow* window;
	
	if (!glfwInit()) { return -1; }

	// open gl v3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Reality Display Processor", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSwapInterval(3);

	GLenum initResult = glewInit();
	if (GLEW_OK != initResult) {
		std::cout << "error initializing OpenGL\n";
	}

	std::cout << "Rendering...\nOpenGL version " << glGetString(GL_VERSION)
		<< "\nGLEW version " << glewGetString(GLEW_VERSION);

	unsigned int buffer_object;
	unsigned int index_buffer_object;
	unsigned int vertex_array_object;
	int num_indicies = 6;
	createBuffer(buffer_object, index_buffer_object, vertex_array_object);

	int vertex_index_to_bind = 0;
	int num_floats_per_vertex = 2;
	bindVertex(vertex_index_to_bind, num_floats_per_vertex);

	ShaderVertexArray optimized_shader;
	ShaderVertexArrayProgramSource source = optimized_shader
		.parseShader("res/shaders/BasicUniform.shader"); // ensure debug working dir is relative to $(ProjectDir)

	unsigned int shader_bits = optimized_shader
		.createShader(source.VertextSource, source.FragmentSource);
	glUseProgram(shader_bits);
	
	// every uniform has a name as it's id
	GLCall(int location = glGetUniformLocation(shader_bits, "u_color"));
	ASSERT(location != -1);
	GLCall(glUniform4f(location, 0.5f, 0.2f, 0.7f, 1.0f));

	// * * * * * * * * * * * *
	// first unbind everything
	// * * * * * * * * * * * *
	// http://docs.gl/gl4/glBindBuffer
	/*Buffer object names are unsigned integers.The value zero is reserved, but there is no default buffer object for each buffer object target.Instead, buffer set to zero effectively unbinds any buffer object previously bound, and restores client memory usage for that buffer object target(if supported for that target).*/
	glBindVertexArray(0); // clear the mem for vertex bufer binding
	glUseProgram(0); // was shader_bits
	glBindBuffer(GL_ARRAY_BUFFER, 0); // was buffer_object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // was index_buffer_object

	float blue = 0.7f;
	float increment = 0.05f;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// * * * * * * * * * * * * *
		// then bind everything back
		// * * * * * * * * * * * * *
		// 1. bind shader and setup uniform
		glUseProgram(shader_bits);
		GLCall(glUniform4f(location, 0.5f, 0.2f, blue, 1.0f));
		// 2. bind vertex buffer and set mem layout NOT needed anymore
		// glBindBuffer(GL_ARRAY_BUFFER, buffer_object);
		// glEnableVertexAttribArray(params);
		// glVertexAttribPointer(params);
		// 3. bind index buffer
		// all replaced with the next line that links vertex buffer to vertex array object
		GLCall(glBindVertexArray(vertex_array_object));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
		
		// use below for index buffer
		// triple AAA games use me :)
		GLCall(glDrawElements(GL_TRIANGLES, num_indicies, GL_UNSIGNED_INT, nullptr)); // nullptr since we bind buffers using glGenBuffers
		
		if (blue > 1.0f) {
			increment = -0.05f;
		}
		else if (blue < 0.0f) {
			increment = 0.05f;
		}

		blue += increment;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shader_bits);
	glfwTerminate();

	return 0;
}

void BufferVertexArray::createBuffer(unsigned int& buffer, unsigned int& index_buffer, unsigned int& vao)
{
	const int buffer_object_size = 8;
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

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,
		buffer_object_size * sizeof(float),
		triangle_verticies,
		GL_STATIC_DRAW);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	// layout of vertext data 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		index_buffer_object_size * sizeof(unsigned int),
		indicies,
		GL_STATIC_DRAW);
}

void BufferVertexArray::bindVertex(unsigned int index_to_bind, unsigned int num_floats_per_vertex) {
	bool normalize = GL_FALSE;
	GLsizei mem_address_width_vertex_to_vertex = sizeof(float) * num_floats_per_vertex; // num of bytes for each verticies in memory
	GLCall(glEnableVertexAttribArray(index_to_bind));
	// fucntion naming makes it seem like this data is all tied/bound to buffer, but no. underneath it's tied/bound to vertex array object
	// it being the state of our data, how our data is structured
	glVertexAttribPointer(index_to_bind,
		num_floats_per_vertex,
		GL_FLOAT,
		normalize,
		mem_address_width_vertex_to_vertex,
		0);
}