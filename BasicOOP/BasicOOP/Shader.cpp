#include "Renderer.h"

#include "Shader.h"

Shader::Shader(const std::string& file_path) 
	: m_file_path(file_path), m_renderer_id(0)
{
	// ensure debug working dir is relative to $(ProjectDir)
	ShaderSource shaderSource = parse_shader(m_file_path);
	m_renderer_id = create_shader(shaderSource.vertex_source, shaderSource.fragment_source);
}

Shader::~Shader() 
{ 
	MyGLCall(glDeleteProgram(m_renderer_id));
}

void Shader::bind() const 
{
	MyGLCall(glUseProgram(m_renderer_id));
}

void Shader::bind_fragment_location(int location, std::string name) const
{
	MyGLCall(glBindFragDataLocation(m_renderer_id, location, name.c_str()));
}

void Shader::unbind() const 
{ 
	MyGLCall(glUseProgram(0));
}

void Shader::set_uniform1i(const std::string& name, int i)
{
	MyGLCall(glUniform1i(get_uniform_location(name), i)); 
}

void Shader::set_uniform1f(const std::string& name, float f)
{
	MyGLCall(glUniform1f(get_uniform_location(name), f));
}

void Shader::set_uniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
	// 0x0502 GL_INVALID_OPERATION ERROR is okay? exe still runs
	// BUT NOT always, get this fixed
	int l = get_uniform_location(name);
	MyGLCall(glUniform4f(l, f1, f2, f3, f4));
}

void Shader::set_uniform_mat4f(const std::string& name, const glm::mat4& matrix)
{
	// GL_FALSE, do not transpose since glm stores data in column major format, exactly what OpenGL expects,
	int num_matricies = 1;
	MyGLCall(glUniformMatrix4fv(get_uniform_location(name), num_matricies, GL_FALSE, &matrix[0][0]));
}

ShaderSource Shader::parse_shader(const std::string& file_path)
{
	std::ifstream stream(file_path);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream str_stream[2];
	ShaderType shaderType = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) { // npos is invald string position
			if (line.find("vertex") != std::string::npos) {
				shaderType = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				shaderType = ShaderType::FRAGMENT;
			}
		}
		else {
			str_stream[(int)shaderType] << line << '\n';
		}
	}

	return { str_stream[0].str(), str_stream[1].str() };
}

int Shader::compile_shader(unsigned int type, const std::string& source_text)
{
	unsigned int id = glCreateShader(type);
	const char* raw_source = source_text.c_str(); // alternatly could use &source[0] ptr to mem addr of first char in string - how do we know mem has not been free? 
	MyGLCall(glShaderSource(id, 1, &raw_source, nullptr));
	MyGLCall(glCompileShader(id));

	int result;
	MyGLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		MyGLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char)); // allocate this mem on the stack
		MyGLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "\nERROR ShaderVertexArray::compileShader for type " <<
			(type == GL_VERTEX_SHADER ? "fragment" : "vertex")
			<< "shader\n" << message << '\n';
		MyGLCall(glDeleteShader(id));

		return 0;
	}

	return id;
}

int Shader::create_shader(const std::string& vertex_shader_text, const std::string& fragment_shader_text)
{
	MyGLCall(unsigned int program = glCreateProgram());
	unsigned int v_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_text);
	unsigned int f_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_text);

	MyGLCall(glAttachShader(program, v_shader));
	MyGLCall(glAttachShader(program, f_shader));
	MyGLCall(glLinkProgram(program));
	MyGLCall(glValidateProgram(program));
	// once linked to program .exe we can delete these obj intermediate file bits
	MyGLCall(glDeleteShader(v_shader));
	MyGLCall(glDeleteShader(f_shader));

	return program;
} 

int Shader::get_uniform_location(const std::string& name)
{	
	if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end()) {
		return m_uniform_location_cache[name];
	}

	int location;
	MyGLCall(location = glGetUniformLocation(m_renderer_id, name.c_str()));
	if (location == -1) {
		std::cout << "WANRING: uniform '" << name << "' does not exisits.\n";
	}
	m_uniform_location_cache[name] = location;

	return location;
}