#version 430 core

smooth in vec3 color;

void main()
{
  gl_FragColor = vec4(color,1);
}
