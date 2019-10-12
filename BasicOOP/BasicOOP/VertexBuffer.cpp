#include "Renderer.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	MyGLCall(glGenBuffers(1, &m_renderer_id));
	MyGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
	MyGLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	MyGLCall(glDeleteBuffers(1, &m_renderer_id));
}

void VertexBuffer::bind() const
{
	MyGLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void VertexBuffer::unbind() const
{
	MyGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
