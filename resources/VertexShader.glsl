#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 translation;
uniform mat4 scale;

void main()
{
    gl_Position = scale * vec4(aPos.x + translation.x, aPos.y + translation.y, aPos.z + translation.z, 1.0);
}