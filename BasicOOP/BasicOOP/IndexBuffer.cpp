#include "Renderer.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, 
	unsigned int num_of_indicies) : m_num_of_indicies(num_of_indicies)
{
	// GLuint May be better, some platforms int may not be 4 bytes
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	MyGLCall(glGenBuffers(1, &m_renderer_id));
	MyGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
	MyGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		num_of_indicies * sizeof(unsigned int), 
		data, 
		GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	MyGLCall(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::bind() const
{
	MyGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::unbind() const
{
	MyGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int const IndexBuffer::get_num_of_indicies()
{
	return m_num_of_indicies;
}
