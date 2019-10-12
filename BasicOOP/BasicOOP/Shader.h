#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

#include "glm\glm.hpp"

struct ShaderSource
{
	std::string vertex_source;
	std::string fragment_source;
};

class Shader
{
private:
	std::string m_file_path;
	unsigned int m_renderer_id;
	// cache uniform location so we don't need to grab it each time we get the uniform location
	// uniforms are alwasy 32 bit ints, not unsigned ints 
	std::unordered_map<std::string, int> m_uniform_location_cache;

public:
	Shader(const std::string& file_path);
	~Shader();

	void bind() const;
	void unbind() const;

	void set_uniform1i(const std::string& name, int i);
	void set_uniform1f(const std::string& name, float f); 
	void set_uniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix);

private:
	ShaderSource parse_shader(const std::string& file_path);
	int compile_shader(unsigned int type, const std::string& source_text);
	int create_shader(const std::string& vertex_shader_text, const std::string& fragment_shader_text);
	int get_uniform_location(const std::string& name);
};

#endif /* SHADER_H */
