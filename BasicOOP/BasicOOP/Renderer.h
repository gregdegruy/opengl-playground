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
	float m_increment_color;
public:
	Renderer();
	void clear() const;
	void draw(Shader& shader, VertexArray& vertex_array, IndexBuffer& index_buffer) const;
	void draw_glow_quad(Shader& myshader, VertexArray& vertex_array, IndexBuffer& index_buffer, float& color, std::string uniform, std::string mvp_uniform);
};

#endif /* RENDERER_H */
