#version 330 core

//------------------------------------------

layout ( location = 0 ) in vec3 in_Position;
layout ( location = 2 ) in vec2 in_TexCoord;
layout ( location = 5 ) in vec2 in_TexCoord_LightMap;

//------------------------------------------

out vec3 Position;
out vec2 TexCoord;
out vec2 TexCoord_LightMap;

//------------------------------------------

uniform mat4 PVMatrix;

//------------------------------------------

void main()
{		
	gl_Position = PVMatrix * vec4( in_Position, 1.0f );

	Position = in_Position;
	TexCoord = in_TexCoord;
	TexCoord_LightMap = in_TexCoord_LightMap;
}