#include <iostream>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class HelloDebugger
{
public:
	HelloDebugger();
	void GLClearError();
	bool GlLogCall(const char* function, const char* file, int line);
};

