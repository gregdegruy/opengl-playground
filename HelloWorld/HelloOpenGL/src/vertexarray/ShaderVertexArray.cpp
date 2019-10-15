#include "ShaderVertexArray.h"

ShaderVertexArray::ShaderVertexArray() {}

ShaderVertexArrayProgramSource ShaderVertexArray::parseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);	
	
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType shaderType = ShaderType::NONE;
	while (getline(stream, line)) 
	{
		if (line.find("#shader") != std::string::npos) { // npos is invald string position
			if (line.find("vertex") != std::string::npos) {
				shaderType = ShaderType::VERTEX;
			} else if (line.find("fragment") != std::string::npos) {
				shaderType = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)shaderType] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int ShaderVertexArray::compileShader(unsigned int type, const std::string& source)
{
	// decouple certain openGL over header like GLuint with unsigned int instead
	unsigned int id = glCreateShader(type);
	const char* raw_source_string = source.c_str(); // &source[0] pointer to memory address of first char in string - how can we know this mem has not been free? 
	glShaderSource(id, 1, &raw_source_string, nullptr);
	glCompileShader(id);

	// error handle
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); // allocate this mem on the stack
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "\nERROR ShaderVertexArray::compileShader for type " <<
			(type == GL_VERTEX_SHADER ? "fragment" : "vertex")
			<< "shader\n" << message << '\n';
		glDeleteShader(id);

		return 0;
	}

	return id;
}

unsigned int ShaderVertexArray::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	glValidateProgram(program);
	// once linked to program .exe we can delete these obj intermediate file bits
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return program;
}