#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray() 
{ 
	MyGLCall(glGenVertexArrays(1, &m_renderer_id));
}

VertexArray::~VertexArray()
{ 
	MyGLCall(glDeleteVertexArrays(1, &m_renderer_id));
}

// bind vertex buffer and set memory layout
void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) 
{
	VertexArray::bind();
	vb.bind();
	const auto& elements = layout.get_elements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) 
	{		
		const auto& element = elements[i];		
		MyGLCall(glEnableVertexAttribArray(i));
		MyGLCall(glVertexAttribPointer(i,
			element.num_vertex_components,
			element.type,
			element.normalized,
			layout.get_stride(),
			(const void*) offset)); // function pointer? https://www.cprogramming.com/tutorial/function-pointers.html
		offset += element.num_vertex_components * VertexBufferLayoutElement::get_size_of_type(element.type);
	}	
}

void VertexArray::bind() const
{
	MyGLCall(glBindVertexArray(m_renderer_id));
}

void VertexArray::unbind() const
{
	MyGLCall(glBindVertexArray(0));
}
