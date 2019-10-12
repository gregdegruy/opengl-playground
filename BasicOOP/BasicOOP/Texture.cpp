#include "Texture.h"

#include "Vendor\stb_image\stb_image.h"

Texture::Texture(const std::string& file_path)
	: m_file_path(file_path), m_local_buffer(nullptr), m_height(0), m_width(0),
	m_bits_per_pixel(0)
{
	stbi_set_flip_vertically_on_load(1);
	// passing ptrs so stbi can use mem addr to write to our vars
	m_local_buffer = stbi_load(file_path.c_str(), &m_width, &m_height, &m_bits_per_pixel, 4); // 4 channels RGBA

	MyGLCall(glGenTextures(1, &m_renderer_id));
	MyGLCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

	// all 4 needed or else black texture applied
	// Linear resample of image
	MyGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	MyGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // magnification
	MyGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // horiz wrap and clamp/do not extend the texture
	MyGLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // tiling as in tile

	// give OpenGL our Texture data
	// GL_RGBA8 "internalFormat" (8 bits per channel) is more supported now internalFormat tells OpenGL how our texture data is stored
	// GL_RGBA "format" of that bit (m_local_buffer) data we are providing to OpenGL
	MyGLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer));
	// unbind
	MyGLCall(glBindTexture(GL_TEXTURE_2D, 0));

	// buffer contains data? free mem
	if (m_local_buffer) {
		stbi_image_free(m_local_buffer);
	}
}

Texture::~Texture()
{
	MyGLCall(glDeleteTextures(1, &m_renderer_id));
}

void Texture::bind(unsigned int slot) const
{
	MyGLCall(glActiveTexture(GL_TEXTURE0 + slot));
	MyGLCall(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void Texture::unbind()
{
	MyGLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
