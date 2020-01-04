#include <iostream>

#include "GL1Hello\HelloWindow.h"
#include "GL2VertexAndShader\VertexBufferAndShader.h"
#include "GL3VertAndShaderRefactor\VertexBufferOpt.h"
#include "GL4Debug\DebugBuffer.h"
#include "GL5Uniforms\UniformBuffer.h";
#include "GL6VertexArray\BufferVertexArray.h"

int main(void)
{
	HelloWindow helloWindow;
	VertexBufferAndShader vertexBufferAndShader;
	VertexBufferOpt vertexBufferOpt;
	DebugBuffer debugBuffer;
	UniformBuffer uniformBuffer;
	BufferVertexArray bufferVertexArray;

	enum demo 
	{
		HELLO,
		VERTEX_SHADER,
		VERTEX_SHADER_OPTIMIZED,
		DEBUG_BUFFER,
		UNIFORMS,
		VERTEX_ARRAY
	};

	int success; 
	int choice;
	char done;			
	bool running = true;
	while (running)
	{
		std::cout << "Requiescat in pace: " << '\n';
		std::cout <<
			"(1) Hello World\n" <<
			"(2) Vertex Buffer\n" <<
			"(3) Vertex Buffer Optimized\n" <<
			"(4) Debug Buffer\n" <<
			"(5) Vertex Array\n";
		std::cin >> choice;

		switch (choice)
		{
		case HELLO:
			success = helloWindow.run();
			break;
		case VERTEX_SHADER:
			success = vertexBufferAndShader.run();
			break;
		case VERTEX_SHADER_OPTIMIZED:
			success = vertexBufferOpt.run();
			break;
		case DEBUG_BUFFER:
			success = debugBuffer.run();
			break;
		case UNIFORMS:
			success = uniformBuffer.run();
			break;
		case VERTEX_ARRAY:
			success = bufferVertexArray.run();
			break;
		default:
			break;
		}

		std::cout << "\n\nDone? \"y\" or \"n\"";
		std::cin >> done;
		switch (done)
		{
		case 'y':
			running = false;
		case 'n':
			continue;
		default:
			std::cout << "Done? \"y\" or \"n\"";
			std::cin >> done;
		}
	}	

	return success;
}
