TheChernoProject OpenGL

OepnGL Docs http://docs.gl/, OpenGL is a state machine
The OpenGL Extension Wrangler Library
&
GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.

Buffer - area of memory uninterrupted flow of information


1. HellowWindow
	* Using glfw for OpenGL with include headers and libs.
	* Using glew for accessing driver methods through pointers with include headers and libs. GLEW_STATIC required in preprocessor defintions
	* All with libs for static linking not dlls.

2. VertexBuffer - vertandshaders, and opt (optimized)
	* Objects in memory, array of vertex data > ints > bytes > bits all
		unsigned int buffer;
		unsigned int index_buffer_object;
		Stack allocated... i think... memory is reserved for these two unsigned ints. Then, we use OpenGL to fill the array of ints in memory with our vertext data
	* Optimize tri creation of legacyDrawTriangle using buffers
	* Uses glGenBuffers creates graphics data in GPUs VRAM, all buffer data is identified uniquely as a collection of bits
	* Pipeline: 
		* graphics data in buffer > shader reads data > shader transforms data to onscreen graphics (called on each vertex) 
			> fragment shader rasterizes triangle filling it in with pixels (called on each pixel)
	* Buffer has the vertext data
	* Shader reads data from each vertext in buffer after we tell it how memory is structured, some drivers provide default shader to you and 
	will allow for triangle to be properly rendered on screen without using a shader to grab buffer data
	* Shaders common
		* Vertext Shaders
		* Fragment shaders aka pixel shaders

3. IndexBuffer, VertexBuffer and Shader Optimized 
	* Triangle, a TRI, is the most primative graphics element we can express with a normal
	* Created clear steps for createBuffer and bindVertex using the index of the vertex we want to bind, scope appears to be understood within functions
	* Read from and parse shader tokens from file
		* Using enum to capture shader type and ShaderProgramSource struct to store shader source code string
	* IndexBuffer to reuse memory for vertex overlap between tris
	* glDrawElements triple AAA games use me :)

4. Debug
	* glDebugMessageCallback for error handling
	* Must clear all errors and capture the most recent error at the render step you want to debug
	* This error handling will present an error code in hex that you can search for in glew.h
		* My example passes the wrong type of enum to the 3rd param of glDrawElements, error code 0x500 you can search for in glew.h GL_INVALID_ENUM
	* Macros!!!
		* With a macro, #define we use __debugbreak supported in the Microsoft MSVC compiler, the debugger will break exactly where the program error happens
		* Our GLCall marco can wrap the function we suspect has issues to capture the error AND is smart enough to know the file and line we failed at
			* We can wrap all functions with this GLCall macro... but is that efficent???

5. Unfiorms
	* Load data from CPU into GPU, this uniform is added in the shader file, then loaded into the buffer using glUniform4f and defining the color code directly in the cpp file
	* Uniform calls in this implementation are done on each draw and applied to all drawn objects	
	* This allows us to add a small flashing animation, glfwSwapInterval(3) is used to control the framerate of this color swap

6. VAO Vertex Array Object - Vertex Arrays in OpenGL
	* Since we're using the OpenGL compatability profile mode gives us a Vertex Array at index 0, #core profile need to create a Vertex Array object ourselves
	* Notice
		unsigned int buffer_object;
		unsigned int index_buffer_object;
		Stack allocated... i think... memory is reserved for these two unsigned ints. Then, we use OpenGL to fill the array of ints in memory with our vertext data
	* In line 59 of our buffer object we do the things
	* When drawing multiple objects, need to rebind each time, too much compute
	* Unbind program, buffer and index buffer objects. The bind them all during draw time while (!glfwWindowShouldClose(window)) {}
	* OLD DRAW PIPELINE for our single TRIANGLE
		* Bind shader > Bind vertex buffer > Setup vertex memory layour > bind index buffer > DRAW
	* NEW DRAW PIPELINE
		* Bind shader > Bind vertex array > Bind index buffer > DRAW
		* Vertex array has state of all objects we want to draw
	* Using glfwWindowHint to define open gl v3.3 and core profile, instead of using the one our latest one in our drivers
	* Create a VAO using glGenVertexArrays
	* APPROACH
		* One VAO for the life of the program OR Seperate VAO for each piece of geometry in the program
		* One VAO is proven faster, try global first, benchmark, but depends on the use case in the REAL WORLD