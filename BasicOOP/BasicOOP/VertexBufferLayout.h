#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>

#include <GL\glew.h>

#include "Renderer.h"

struct VertexBufferLayoutElement
{
	// follows param list for the first c spec param list http://docs.gl/gl4/glVertexAttribPointer
	// nice mem alignment bro, mem size on most machines is
	unsigned int num_vertex_components;	// 4 bytes
	unsigned int type;					// 4 bytes
	unsigned char normalized;			// 1 byte
	static unsigned int get_size_of_type(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(true);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	unsigned int m_stride; // vertex_mem_address_width
	std::vector<VertexBufferLayoutElement> m_elements;
public:
	VertexBufferLayout() 
		: m_stride(0) { }

	template<typename T>
	void push(unsigned int num_vertex_components)
	{
		static_assert(false);
	}
	// these 3 templates MUST use the format above
	template<>
	void push<float>(unsigned int num_vertex_components)
	{
		m_elements.push_back({ num_vertex_components, GL_FLOAT, GL_FALSE });
		m_stride += num_vertex_components * VertexBufferLayoutElement::get_size_of_type(GL_FLOAT);
	}
	template<>
	void push<unsigned int>(unsigned int num_vertex_components)
	{
		m_elements.push_back({ num_vertex_components, GL_UNSIGNED_INT, GL_FALSE });
		m_stride += num_vertex_components * VertexBufferLayoutElement::get_size_of_type(GL_UNSIGNED_INT);
	}
	template<>
	void push<unsigned char>(unsigned int num_vertex_components)
	{
		m_elements.push_back({ num_vertex_components, GL_UNSIGNED_BYTE, GL_TRUE });
		m_stride += num_vertex_components * VertexBufferLayoutElement::get_size_of_type(GL_UNSIGNED_BYTE);
	}

	// need const& here?
	inline const std::vector<VertexBufferLayoutElement> get_elements() const { return m_elements; }
	inline unsigned int get_stride() const { return m_stride; }
};

#endif /* VERTEXBUFFERLAYOUT_H */
