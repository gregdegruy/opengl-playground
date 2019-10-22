#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texture_coordinate;

out vec2 varying_texture_coordinate;

uniform mat4 u_modelview_projection_matrix;

void main()
{
	gl_Position = u_modelview_projection_matrix * position;
	varying_texture_coordinate = texture_coordinate;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 quad_color;
layout(location = 1) out vec4 texture_color;

in vec2 varying_texture_coordinate;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{	
	quad_color = u_color;
	vec4 texture_color = texture(u_texture, varying_texture_coordinate);
	texture_color = texture_color;
};