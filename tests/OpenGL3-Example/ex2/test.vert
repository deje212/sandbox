#version 430 core

layout(location=0) in vec3 vpos;
layout(location=1) in vec3 vcolor;

smooth out vec3 color;

void main()
{
  color = vcolor;
  gl_Position = vec4(vpos, 1.0);
}
