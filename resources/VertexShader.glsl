#version 330 core
layout (location = 0) in vec4 aPos;

uniform float ratio;

void main()
{
    gl_Position = vec4(aPos.x/ratio, aPos.y, aPos.z ,1.0);
}