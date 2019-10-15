#include "hello\HelloWindow.h"
#include "vertexandshaders\VertexBufferAndShader.h"
#include "vertandshadersoptimized\VertexBufferOpt.h"
#include "debug\DebugBuffer.h"
#include "uniforms\UniformBuffer.h";
#include "vertexarray\BufferVertexArray.h"

int main(void)
{
	HellowWindow hellowWindow;
	VertexBufferAndShader vertexBufferAndShader;
	VertexBufferOpt vertexBufferOpt;
	DebugBuffer debugBuffer;
	UniformBuffer uniformBuffer;
	BufferVertexArray bufferVertexArray;

	int success = 0;

	success = bufferVertexArray.run();

	return success;
}