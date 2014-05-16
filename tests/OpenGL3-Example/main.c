#include <GL/glfw.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

#define BUFFER_OFFSET(ofs) (NULL + (ofs))

static unsigned int shaders_program;

static void         InitOpenGL(void);
static char        *LoadText(const char *filename);
static void         LoadShaders(void);
static unsigned int CreateVAO(void);
static void         DrawVAO(int vao, size_t triangles);

int main(void)
{
  if (glfwInit() == GL_FALSE)
  {
    fprintf(stderr, "initializing graphics library");
    exit(EXIT_FAILURE);
  }

  /* For now on, glfwPollEvents() must be explicitly called! */
  glfwDisable(GLFW_AUTO_POLL_EVENTS);

  /* Using OpenGL 3.0 core profile! */

  /* if GLX_ARB_create_context extension is not available, then 
       setting OpenGL version is partially supported. 
     if GLX_ARB_create_context_profile is not available, then
       setting GLFW_OPENGL_CORE_PROFILE will cause glfwOpenWindow() to fail. */
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
  if (glfwExtensionSupported("GLX_ARB_create_context_profile"))
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* if GLX_ARB_multisample extension is not available, than this has no effect. */
  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	/* Set FULLSCREEN MODE */
	if ( !glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
      								8, 8, 8, 8, /* rgba bits */
                      24,         /* depth buffer bits */
                      0,          /* stencil buffer bits */
                      GLFW_WINDOW) )
	{
    glfwTerminate();
    fprintf(stderr, "cannot open window");
    exit(EXIT_FAILURE);
  }

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  int major, minor, rev;
  glfwGetGLVersion(&major, &minor, &rev);
  printf ("Renderer: %s\n", renderer);
  printf ("OpenGL version supported %s\n", version);
  printf ("GLFW reports OpenGL version %d.%d.%d\n", major, minor, rev);

  /* Make sure mouse cursor is invisible after initialization. */
  glfwDisable(GLFW_MOUSE_CURSOR);

  InitOpenGL();
  LoadShaders();
  unsigned int vao = CreateVAO();

  glUseProgram(shaders_program);

  for (;;)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* NOTE: VAO already bound here! */
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();

    if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
      break;

    glfwSwapBuffers();
  }
  
  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}

// Initializa OpenGL.
static void InitOpenGL(void)
{
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  glClearColor(0, 0, 0, 1);
  glClearDepth(1);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable (GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

  // OBS: Matrices are deprecated on OpenGL 3.0+ core profile.
}

static char *LoadText(const char *filename)
{
  long filesize;
  char *buffer = NULL;
  FILE *fin;
  jmp_buf jb;
    
  if ((fin = fopen(filename, "rb")) != NULL)
  {
    if (setjmp(jb))
    {
      fclose(fin);
      return NULL;
    }

    fseek(fin, 0L, SEEK_END);
    filesize = ftell(fin);
    fseek(fin, 0L, SEEK_SET);

    if ((buffer = malloc(filesize+1)) == NULL)
      longjmp(jb, 1);

    if (fread(buffer, filesize, 1, fin) != 1)
    {
      free(buffer);
      longjmp(jb, 1);
    }

    *(buffer + filesize) = '\0';

    fclose(fin);
  }

  return buffer;
}

/* Load, compile and link shaders. */
static void LoadShaders(void)
{
  char *vertex_shader; 
  char *fragment_shader;
  int status;
  int len;
  char log[256];
  unsigned int vs, fs;

  vertex_shader = LoadText("simple.vert");
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  free(vertex_shader);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    glGetShaderInfoLog(vs, sizeof(log)-1, &len, log);
    fprintf(stderr, "Error compiling vertex shader:\n\t%s\n", log);
    exit(EXIT_FAILURE);
  }

  fragment_shader = LoadText("simple.frag");
  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  free(fragment_shader);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    glGetShaderInfoLog(fs, sizeof(log)-1, &len, log);
    fprintf(stderr, "Error compiling fragment shader:\n\t%s\n", log);
    exit(EXIT_FAILURE);
  }

  shaders_program = glCreateProgram();
  glAttachShader(shaders_program, vs);
  glAttachShader(shaders_program, fs);

  /* Need to be defined here! 
     FIXME: GLSL 4+ use layout(location=n)... is this necessary then? */
  glBindAttribLocation(shaders_program, 0, "vrtx"); /* VertexAttribPointer index 0 is vertex data. */
  glBindAttribLocation(shaders_program, 1, "clr");  /* VertexAttribPointer index 1 is color data. */

  glLinkProgram(shaders_program);
  glGetProgramiv(shaders_program, GL_LINK_STATUS, &status);
  if (!status)
  {
    glGetProgramInfoLog(vs, sizeof(log)-1, &len, log);
    fprintf(stderr, "Error linking shaders program:\n\t%s\n", log);
    exit(EXIT_FAILURE);
  }
}

static unsigned int CreateVAO(void)
{
  /* array will disapear after the function returns. */
  float points[] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };

  float colors[] = {
     0.0f,  0.0f, 1.0f, 1.0f,
     0.0f,  1.0f, 0.0f, 1.0f,
     1.0f,  0.0f, 0.0f, 1.0f
  }; 

  unsigned int vao, vbo[2];

  // VAOs is a container of Buffer Objects and VertexAttribs.
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(2, vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, BUFFER_OFFSET(0));

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, 0, 0, BUFFER_OFFSET(0));

  // Para teste (UnBind).
  //glBindVertexArray(0);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);

  return vao;
}


