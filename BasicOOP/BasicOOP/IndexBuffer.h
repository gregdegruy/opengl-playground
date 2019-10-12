#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer
{
private:
	unsigned int m_renderer_id;
	unsigned int m_num_of_indicies;
public:
	IndexBuffer(const unsigned int* data, unsigned int num_of_indicies);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int const get_num_of_indicies();
};

#endif /* INDEXBUFFER_H */
