#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define MyGLCall(x) MyGLClearError();\
	x;\
	ASSERT(MyGLLogCall(#x, __FILE__, __LINE__))

void MyGLClearError();
bool MyGLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
		
public:
	void clear() const;
	void draw(Shader& shader, VertexArray& vertex_array, IndexBuffer& index_buffer, float blue) const;
};



#endif /* RENDERER_H */
