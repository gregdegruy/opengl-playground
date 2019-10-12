# TheChernoProject OpenGL

MEMORY
	* Vertex Buffer

	* Vertex Buffer Layout

	* Vertex Array

	* Index Buffer

GRAPHICS
	* Shader

	** Blending

	* Textures

	** Materials

RENDER
	* Renderer


Every OpenGL call should involve the GPU in some way
Abstracting OpenGL into Classes
https://www.youtube.com/watch?v=bTHqmzjm2UI&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=13
Almost last vid in this Classes series Writing a Basic Renderer in OpenGL
https://www.youtube.com/watch?v=jjaTTRFXRAk&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=16
Uses unsigned int too much? https://youtu.be/n4k7ANAFsIQ?t=1208

https://github.com/nigels-com/glew
Docs https://www.glfw.org/documentation.html
*** OpenGL stores data in column major format, data is read in column by column ***

On screen GUI https://github.com/ocornut/imgui

## Visual Studio 2019 Setup
C/C++
	General - $(SolutionDir) to where GLFW and glew includes are located
	Preprocessor - specify first Preprocessor Definition as GLEW_STATIC;
Linker
	General - $(SolutionDir) to where GLFW and glew static libs are located
	Input - List the libs glfw3.lib;User32.lib;Gdi32.lib;Shell32.lib;opengl32.lib;glew32s.lib

## DRAW PIPELINE
Bind shader > Bind vertex array > Bind index buffer > DRAW
		* Vertex buffer has our graphics bytes
		* Vertex array defines the memory layout of our vertex buffer
		* Vertext buffer layout defines mem addr structure
		* Shader and Texture adds the color and image graphics respectively respectfully
		* Draw earch frame on Window


## UNBIND
	Generally don't need to call unbind since going to bind something new anyway

Main Abstractions

MEMORY
	* Vertex Buffer
		Size of our queued up graphics data
		Tri verticies

	* Vertex Buffer Layout
		Struct for containing our vertex buffer attributes for our glVertexAttribPointer
		Vector of this struct
			Stride for vertex_mem_address_width between verts in our vector
			Push to add m_elements to our Buffer layout
		Ploymorphic funtion to store floats, int, and bytes

	* Vertex Array
		Adds collection of VertexBuffers with offsets
		Binds the vertex buffers and set memory layout

	* Index Buffer
		Loads rendundant vertex data during drawing
		Supporting 32 bit indicies

	* Vertex Buffer & Index Buffer
		Has a Renderer ID that uniquely identifies each Vertex Buffer
		Can bind, unbind with renderer id holding our pointer to the binded data

GRAPHICS
	* Shader
		Written in GLSL (OpenGL Shading Language)
		#shader vertex (aka pixel) fills in the plane we INput here
		#shader fragment for each pixel adds color we OUTput here
		Uniform shader variables that are constant from one Shader (instantiation?call?) to the next
		Compile source text of shader
		Major changes in vid "Shader Abstraction in OpenGL"
		SAMPLING with `varying_texture_coordinate` in UniformTexture.shader to get a lookup of the exact coordinate to the texture we're drawing
		// runs once per vertex (aka pixel), projection matrix puts pixel in right place on screen to maintain ratio
		gl_Position = u_modelview_projection_matrix * position;
		//
		// this gl_Position = assingment is VERY important vertext positions are multipled by our matrix to keep the

		// GREAT PROJECTION EXAMPLE
		// use this result is a great test that shows how we convert from the 100 to 100 vertex to the -1 to 1 device coordinate space
		glm::mat4 orthographic_projection_matrix
			= glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

		glm::vec4 vertex_position(100.0f, 100.0f, 0.0f, 1.0f);
		glm::vec4 result = orthographic_projection_matrix * vertex_position;

		//
		//
		notice in fragment shader, the last color output overwrites our texture color with the value white.
		void main()
		{
			vec4 texture_color = texture(u_texture, varying_texture_coordinate);
			color = texture_color;
			color = vec4(1.0);
		};

	** Blending
		Could use what OpenGL provides, SRC_ALPHA 0 means completely transparent
			`MyGLCall(glEnable(GL_BLEND));`
			`MyGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));`
		or do your own
		Render a transparent thing AND render a red squrare glass and blue square glass on top of each other will get a purple square when looking head on
		Combine both using `glBlendFunc` into an "output color" and store in a "target buffer""
			Take each RGBA color channel for square1 and square2 then do math on each
		example
			sqaure1 RGBA (1.0, 1.0, 1.0, 0.5) SOURCE
			sqaure2 RGBA (1.0, 0.0, 1.0, 1.0) DESTINATION
			R = (Rsrc * Asrc) - (Rsrc * (Asrc - Adest))

	* Textures
		Image file (PNG or whatever) loaded into CPU mem and Shader draws it reading pixel array and defining what color is for earch array element
		Pixel array stored on GPU as a texture
		https://github.com/nothings/stb depends on image loader header file from this repo
			OpenGL bottom left is (0,0) so we must flip it to display correct. Commonly as with scane lines it's usually the top left that's (0,0)
		Slots to bind textures to, most desktops have 32 slots

	** Materials
		Shader and all it's uniforms, not implemented

RENDER
	* Renderer - Draw Factory
		Draw, given Vertex Array, Index Buffer and Shader


* Math
	Matrix
	Vector - directional or positional (where does ball go, where does camera go?)

## Some Concepts yo
	SAMPLING, openGL uses 0 to 1 and scales depending on resolution and interpolates the color to fill in between for earch pixel in the screen coordinates.
	QUADS squares
	TRIS triangles
	PROJECTION MATRIX https://github.com/g-truc/glm
		Help image maintain aspect ratio on different screen sizes
		Orthographic Matrix for 2D mostly  時々{ときどき}
		Perspective Matrix	for 3D
	MODEL VIEW PROJECTION MATRIX
		VIEW MATRIX code to control camera (simulated by translating all on screen objects)
		MODEL MATRIX code for our object (has position, rotatation, and scale)

