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

// http://docs.gl/gl4/glBindBuffer
//
// Buffer object names are unsigned integers. The value zero is reserved, but there is no
// default buffer object for each buffer object target. Instead, buffer set to zero
// effectively unbinds any buffer object previously bound, and restores client memory
// usage for that buffer object target(if supported for that target).
//
void VertexBuffer::unbind() const
{
	MyGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
