#shader vertex
#version 410 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(0.0, 0.98, 0.64, 1.0);
};