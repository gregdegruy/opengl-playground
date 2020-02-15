# TheChernoProject OpenGL

[OpenGL Docs](http://docs.gl/). OpenGL is a state machine.

The OpenGL Extension Wrangler Library (GLEW) & GLFW are Open Source, multi-platform libraries for OpenGL. Provide API for creating windows, contexts and surfaces, receiving input and events.


## HellowWindow
* glfw to call OpenGL APISs.
* glew for accessing driver methods through pointers with include headers and libs.
* Using these both with libs for static linking not dlls.


## VertexBuffer and VertexShaders
Buffers are areas of memory that provide an uninterrupted flow of information.
```
unsigned int buffer;
unsigned int index_buffer_object;
```
Stack allocated(?) memory is reserved for these two unsigned `ints`. Then, we use OpenGL to fill the array of `ints` in memory with our vertex data.
* Buffers can optimize the drawing of triangle, "tris".
* Uses glGenBuffers creates graphics data in GPUs VRAM, all buffer data is identified uniquely as a collection of bits
* Pipeline: 
	> graphics data in buffer > shader reads data > shader transforms data to onscreen graphics (called on each vertex) 
	> fragment shader rasterize triangle filling it in with pixels (called on each pixel)
* Shaders come in the form: Vertex Shaders or Fragment shaders aka pixel shaders.
* Shaders read data from each vertex in our buffer after we tell it how our memory is structured, some libraries provide a shader to you, which can lead to blank white tris being drawn if no shader is provided.


## IndexBuffer, VertexBuffer and Shader Optimized 
* Triangle, a "tri", is the most primitive graphics element we can express with a normal.
* Created clear steps for createBuffer and bindVertex using the index of the vertex we want to bind, scope appears to be understood within functions.
* Read from and parse shader tokens from file:
	* Using enum we can capture shader type and using a ShaderProgramSource struct we store our shader source code string.
* IndexBuffer to reuse memory for vertex overlap between tris.
* `glDrawElements` triple AAA games use me :).


## Debug
* `glDebugMessageCallback` is used for error handling.
* Must clear all errors and capture the most recent error at the render step you want to debug.
* This error handling will present an error code in hex that you can search for in `glew.h`.
	* My example passes the wrong type of enum to the 3rd param of glDrawElements, error code `0x500` which is ` GL_INVALID_ENUM` in `glew.h`.
* Macros
	* `#define` we use `__debugbreak` supported in the Microsoft MSVC compiler, the debugger will break exactly where the program error happens.
	* Our GLCall marco can wrap the function we suspect has issues to capture the error AND is smart enough to know the file and line we failed at.
		* We can wrap all functions with this GLCall macro (efficient?).


## Uniforms
* Load data from CPU into GPU.
* Uniforms are added in the shader file written in `.glsl`, then loaded into the buffer using `glUniform4f`. I define the color code directly in the `cpp` file.
* Uniform calls in this implementation are done on each draw and applied to all drawn objects.
* This allows us to add a small flashing animation, `glfwSwapInterval(3)` is used to control the framerate of this color swap.


## VAO Vertex Array Object - Vertex Arrays in OpenGL
* Since we're using the OpenGL compatibility profile mode gives us a Vertex Array at index 0, `#core profile` is needed to create a Vertex Array object ourselves.
* When drawing multiple objects, need to rebind each time, too much compute right?
* Unbind program, buffer and index buffer objects. Then we bind them all at ONCE during draw time while `(!glfwWindowShouldClose(window)) {}`
* Old draw pipeline for our single tri:
	* Bind shader > Bind vertex buffer > Setup vertex memory layout > bind index buffer > DRAW
* New draw pipeline:
	* Bind shader > Bind vertex array > Bind index buffer > DRAW.
	* Vertex array has state of all objects we want to draw..
* Using glfwWindowHint to define open gl v3.3 and core profile, instead of using the one our latest one in our drivers.
* Create a VAO using `glGenVertexArrays`:
	* Use one VAO for the life of the program OR Separate VAO for each piece of geometry in the program.
	* One VAO is proven faster, try a global first, then benchmark. Overall depends on the use case in the REAL WORLD.
