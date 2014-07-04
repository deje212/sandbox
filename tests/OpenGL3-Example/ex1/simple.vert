#version 130

in vec3 vrtx;
in vec4 clr;

out vec4 fcolor;

void main()
{
  gl_Position = vec4(vrtx, 1.0);
  fcolor = clr;
}
