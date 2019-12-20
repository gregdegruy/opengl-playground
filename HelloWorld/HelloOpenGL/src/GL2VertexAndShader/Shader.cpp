#include "Shader.h"

Shader::Shader() {}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	// decouple openGL overhead like GLuint with unsigned int
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
		std::cout << "\nERROR Shader::compileShader for type " <<
			(type == GL_VERTEX_SHADER ? "fragment" : "vertex") 
			<< "shader\n" << message << '\n';
		glDeleteShader(id);
		
		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
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