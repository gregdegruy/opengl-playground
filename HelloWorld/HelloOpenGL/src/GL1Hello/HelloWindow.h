#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>


class HelloWindow
{
public:
	HelloWindow();
	~HelloWindow();
	int run();
	void legacyDrawTriangle();
};