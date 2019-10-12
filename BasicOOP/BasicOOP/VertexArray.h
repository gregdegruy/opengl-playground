#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"

// FORWARD DECLARE to avoid cyclic reference with renderer declared in the VertexArray.cpp
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_renderer_id;
public:
	VertexArray();
	~VertexArray();

	void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
};

#endif /* VERTEXARRAY_H */
