#include "HelloWindow.h"

HellowWindow::HellowWindow() {}

HellowWindow::~HellowWindow() {
	glfwTerminate();
}

int HellowWindow::run() 
{
	GLFWwindow* window;
	if (!glfwInit()) {
		return -1;
	}
	window = glfwCreateWindow(640, 480, "Reality Coprocessor", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	std::cout << "Rendering...\nOpenGL version " << glGetString(GL_VERSION)
		<< "\nGLEW version " << glewGetString(GLEW_VERSION);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		legacyDrawTriangle();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void HellowWindow::legacyDrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}
