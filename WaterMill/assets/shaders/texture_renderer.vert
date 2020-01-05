#version 430 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertexPosition_modelspace;

layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

uniform mat4 projection;

void main(){

    // Output position of the vertex, in clip space : MVP * position
 	//gl_Position = vertexPosition_modelspace;
	gl_Position = projection * vertexPosition_modelspace;

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
    
}


/*
#version 430 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertexPosition_modelspace;

layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

uniform mat4 projection;
uniform mat4 textureProjection; // NEW


void main(){

    // Output position of the vertex, in clip space : MVP * position
 	//gl_Position = vertexPosition_modelspace;
	gl_Position = projection * vertexPosition_modelspace;

    // UV of the vertex. No special space for this one.
    // UV = vertexUV;
    UV = textureProjection * vertexUV; // NEW
    
}
*/
