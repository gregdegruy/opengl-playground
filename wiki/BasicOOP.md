# Intro

[OpenGL docs](https://www.glfw.org/documentation.html).

Every OpenGL call involves the GPU in some way. OpenGL stores memory in column major format when, data is read in column by column. [Abstracting OpenGL into Classes](https://www.youtube.com/watch?v=bTHqmzjm2UI&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=13) and almost last vid in this series is [Writing a Basic Renderer in OpenGL](https://www.youtube.com/watch?v=jjaTTRFXRAk&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=16).

Depends on: [GL Extension Wrangler](https://github.com/nigels-com/glew), [imgui](https://github.com/ocornut/imgui).

# Draw Pipeline
(CPU) Bind vertex > (CPU) Bind vertex array >(CPU) Bind index buffer > (CPU) Bind shader > (GPU) GLSL fragment and vertex shader > (CPU) Give all to Renderer > (CPU) Renderer.Draw()
* Vertex buffer has our graphics bytes.
* Vertex array defines the memory layout of our vertex buffer.
* Vertex buffer layout defines mem address structure.
* Shader and Texture adds the color and image graphics.
* Draw each frame on Window.

## Unbind
Generally don't need to call unbind since going to bind something new anyway

# Main Abstractions

Memory
* Vertex Buffer
Size of our queued up graphics data
Tri vertices

* Vertex Buffer Layout
Struct for containing our vertex buffer attributes for our glVertexAttribPointer
Vector of this struct
    Stride for vertex_mem_address_width between verts in our vector
    Push to add m_elements to our Buffer layout
Polymorphic function to store floats, int, and bytes

* Vertex Array
Adds collection of VertexBuffers with offsets
Binds the vertex buffers and set memory layout

* Index Buffer
Loads redundant vertex data during drawing
Supporting 32 bit indices

* Vertex Buffer & Index Buffer
Has a Renderer ID that uniquely identifies each Vertex Buffer
Can bind, unbind with renderer id holding our pointer to the bound data

Graphics
* Shader
    * Instructions we give to the GPU
    * GLSL (OpenGL Shading Language) with 2 stages in the pipeline
        * takes in data from vertex data `#shader vertex` (aka pixel shader) fills in the on screen object. output variables to be used in next stage of shader pipeline.
        * takes in output data from vertex shader and uniforms from the cpu `#shader fragment` for each pixel adds color and outputs it to the frame buffer.
    * Uniform shader variables that are constant from one Shader (instantiation?call?) to the next.
    * Compile source text of shader.
    * Major changes in vid "Shader Abstraction in OpenGL".
    * Implement *sampling* with `varying_texture_coordinate` in .shader to get a lookup of the exact coordinate to the texture we're drawing.
    ```
    // runs once per vertex (aka pixel), projection matrix puts pixel in right place on screen to maintain ratio
    gl_Position = u_modelview_projection_matrix * position;
    ```
    * Projection
        * This result is a test that shows how we convert from the 100 to 100 vertex position to the -1 to 1 device * coordinate space.
        ```
         glm::mat4 orthographic_projection_matrix
             = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

         glm::vec4 vertex_position(100.0f, 100.0f, 0.0f, 1.0f);
         glm::vec4 result = orthographic_projection_matrix * vertex_position;
        ```
        * In fragment shader, we can use the last color output to draw our texture with white.
            ```glsl
            void main()
            {
                vec4 texture_color = texture(u_texture, varying_texture_coordinate);
                color = texture_color;
                color = vec4(1.0);
            };
            ```

* Blending
    * Blending colors. Render a red squrare and blue square on top of each other will get a purple square.
    * Combine both colors using `glBlendFunc` into an "output color" and store in a "target buffer"
    * Math is take each RGBA color channel for square1 and square2 then do:
    *     sqaure1 RGBA (1.0, 1.0, 1.0, 0.5) -> SOURCE
    *     sqaure2 RGBA (1.0, 0.0, 1.0, 1.0) -> DESTINATION
    *     red_channel = (Rsrc * Asrc) - (Rsrc * (Asrc - Adest))
    * For transparency OpenGL provides:
        ```
        `glEnable(GL_BLEND)`
        `glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)` // if `SRC_ALPHA = 0` get completely transparent
        ```

* Textures
    * Image files loaded into CPU memory and Shader draws by reading the images pixel array and defining what color is for each array element.
    * Use [stb image loader](https://github.com/nothings/stb) header file.
    * In OpenGL bottom left is (0,0) so we must flip our image.
    * Need "Slots" to bind textures to, most desktops have 32 slots

* Materials
    * Shader and Uniforms.

* Math
    * Matrix
        * Projection matrix
            * Use [glm for math](https://github.com/g-truc/glm).
            * Helps image maintain aspect ratio on different screen sizes.
            * Orthographic Matrix for 2D sometimes 時々{ときどき}.
            * Perspective Matrix for 3D.
                * Matricies are relative to Normalized Device Coordinates, xy plane from -1 to 1.
                * OpenlGL uses 0 to 1 as coordinate space then scales up.
        * Model view projection matrix
            * View matrix control camera (simulated by translating all on screen objects).
            * Model matrix code for our object (has position, rotation, and scale).
    * Vector: directional or positional (where does ball go, where does camera go?).

## Visual Studio 2019 Properties
Solution should target 32 bit `x86` since opengl libs are `0x20` bit compatible.
C/C++
* General: Add GLFW and glew include locations using `$(SolutionDir)`.
* Preprocessor: First Preprocessor Definition as `GLEW_STATIC;`.

Linker
* General: Add GLFW and glew static libs locations using `$(SolutionDir)`.
* Input: List the libs you need, example `User32.lib;Gdi32.lib;Shell32.lib;opengl32.lib;glew32s.lib;glfw3.lib;`.

## Misc. Concepts
* Quads are squares.
* Tris are triangles.
* Sampling: OpenGL uses 0 to 1 and scales depending on resolution and interpolates the color to fill in between for * each pixel in the screen coordinates.
