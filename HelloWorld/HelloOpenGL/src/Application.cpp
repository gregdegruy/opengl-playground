#include "GL1Hello\HelloWindow.h"
#include "GL2VertexAndShader\VertexBufferAndShader.h"
#include "GL3VertAndShaderRefactor\VertexBufferOpt.h"
#include "GL4Debug\DebugBuffer.h"
#include "GL5Uniforms\UniformBuffer.h";
#include "GL6VertexArray\BufferVertexArray.h"

int main(void)
{
	HellowWindow hellowWindow;
	VertexBufferAndShader vertexBufferAndShader;
	VertexBufferOpt vertexBufferOpt;
	DebugBuffer debugBuffer;
	UniformBuffer uniformBuffer;
	BufferVertexArray bufferVertexArray;

	int success = 0;

	success = uniformBuffer.run();

	return success;
}
