#include "GL1Hello\HelloWindow.h"
#include "GL2VertexAndShaders\VertexBufferAndShader.h"
#include "GL3vertandshadersoptimized\VertexBufferOpt.h"
#include "GL4debug\DebugBuffer.h"
#include "GL5uniforms\UniformBuffer.h";
#include "GL6vertexarray\BufferVertexArray.h"

int main(void)
{
	HellowWindow hellowWindow;
	VertexBufferAndShader vertexBufferAndShader;
	VertexBufferOpt vertexBufferOpt;
	DebugBuffer debugBuffer;
	UniformBuffer uniformBuffer;
	BufferVertexArray bufferVertexArray;

	int success = 0;

	success = vertexBufferAndShader.run();

	return success;
}