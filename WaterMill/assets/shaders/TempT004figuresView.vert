#version 430 core
// "offset" is an input vertex attribute
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
// "vs_color" is an output that will be sent to the next shader stage
out vec4 vs_color;

void main(void)
{
	//gl_Positon.xyz = position;
	//gl_Position.w = 1.0;
	gl_Position = position;
	vs_color = color;
}
