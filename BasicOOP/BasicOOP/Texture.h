#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_renderer_id;
	std::string m_file_path;
	unsigned char* m_local_buffer;
	int m_height; 
	int m_width;
	int m_bits_per_pixel;
public:
	Texture(const std::string& file_path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind();

	inline int get_width() const { return m_width; };
	inline int get_height() const { return m_height; };
};

#endif /* TEXTURE_H */
