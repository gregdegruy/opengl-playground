#include "HelloDebugger.h"

HelloDebugger::HelloDebugger()
{

}
void HelloDebugger::GLClearError() 
{
	while (glGetError() != GL_NO_ERROR);
}
bool HelloDebugger::GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "\n[!!! OpenGL ERROR!!!] (0x0" << std::hex << error << ")\n"
			<<  function << "\n" << file << ":" << line << "\n";
		return false;
	}

	return true;
}