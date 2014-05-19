#include <GL/glfw.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

// Macro usada para atribuir offsets aos Vertex Attribute Pointers.
#define BUFFER_OFFSET(ofs) (NULL + (ofs))

// "Handle" do programa contendo shaders.
static unsigned int shaders_program;

static void         InitOpenGL(void);
static char        *LoadText(const char *filename);
static int          LoadShaders(unsigned int *program);
static unsigned int CreateVAO(void);
static void         DrawVAO(int vao, size_t triangles);

int main(void)
{
  /* *** INICIALIZAÇÃO do contexto gráfico usando GLFW 2 *** */
  /* OBS: Por que não uso GLFW 3? Por que não está disponível, por default
          nos repositórios do Debian ou Ubuntu! E já tive problemas ao compilar
          o GLFW 3 para esses ambientes! */
  if (glfwInit() == GL_FALSE)
  {
    fprintf(stderr, "initializing graphics library");
    exit(EXIT_FAILURE);
  }

  /* O tratamento de eventos é feito "manualmente", daqui pra frente. */
  glfwDisable(GLFW_AUTO_POLL_EVENTS);


  /* Usando o core profile do OpenGL 3.0 (uma de minhas máquinas de teste só suporta a versão 3!) */
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);

  /* Se a extensão GLX_ARB_create_context_profile não estiver disponível, então: 
       ajustar o profile é parcialmente suportado e; 
     Se GLX_ARB_create_context_profile não estiver disponível, então
       usar GLFW_OPENGL_CORE_PROFILE fará glfwOpenWindow() falhar! */
  if (glfwExtensionSupported("GLX_ARB_create_context_profile"))
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Se a extensão GLX_ARB_multisample_extension não estiver disponível, então
     ajustar GLFW_FSAA_SAMPLES não tem efeito. */
  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	/* Cria a janela. */
	if ( !glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
      								8, 8, 8, 8, /* rgba bits (8 para cada componente) */
                      24,         /* depth buffer bits (prefiro 24, é mais seguro que seja suportado) */
                      0,          /* Não vamos usar stencil buffer. */
                      GLFW_WINDOW) )
	{
    glfwTerminate();
    fprintf(stderr, "cannot open window");
    exit(EXIT_FAILURE);
  }

// --- Isso está aqui só para eu saber com o que estou lidando.
#ifdef DEBUG
  {
    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    int major, minor, rev;
    glfwGetGLVersion(&major, &minor, &rev);
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    printf ("GLFW reports OpenGL version %d.%d.%d\n", major, minor, rev);
  }
#endif

  /* Vamos sumir com o mouse. */
  glfwDisable(GLFW_MOUSE_CURSOR);

  InitOpenGL();

  if (LoadShaders(&shaders_program) != 0)
    exit(EXIT_FAILURE);
  CreateVAO();
  glUseProgram(shaders_program);

  for (;;)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* NOTE: VAO já está "bound", neste ponto. */
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();

    if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
      break;

    glfwSwapBuffers();
  }
  
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

  /* Liga o teste de profundidade. */
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

// Função auxiliar: Apenas lê um arquivo texto e o coloca num buffer. */
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

/* Carrega, compila e linka os shaders. */
static int LoadShaders(unsigned int *program)
{
  char *vertex_shader; 
  char *fragment_shader;
  int status;
  int len;
  char log[256];
  unsigned int vs, fs;

  if ((vertex_shader = LoadText("simple.vert")) == NULL)
  {
    fprintf(stderr, "Erro carregando Vertex Shader.\n");
    return -1;
  }
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  free(vertex_shader);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    glGetShaderInfoLog(vs, sizeof(log)-1, &len, log);
    fprintf(stderr, "Error compiling vertex shader:\n\t%s\n", log);
    return -1;
  }

  if ((fragment_shader = LoadText("simple.frag")) == NULL)
  {
    fprintf(stderr, "Erro carregando Fragment Shader.\n");
    return -1;
  }
  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  free(fragment_shader);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    glGetShaderInfoLog(fs, sizeof(log)-1, &len, log);
    fprintf(stderr, "Error compiling fragment shader:\n\t%s\n", log);
    return -1;
  }

  *program = glCreateProgram();
  glAttachShader(*program, vs);
  glAttachShader(*program, fs);

  /* Como GLSL 1.3 (do OpenGL 3.0) não tem "layout", nos shaders, então é preciso definir
     a localização de variáveis globais dos shaders aqui. */
  glBindAttribLocation(*program, 0, "vrtx"); /* vertex */
  glBindAttribLocation(*program, 1, "clr");  /* color */

  glLinkProgram(*program);
  glGetProgramiv(*program, GL_LINK_STATUS, &status);
  if (!status)
  {
    glGetProgramInfoLog(vs, sizeof(log)-1, &len, log);
    fprintf(stderr, "Error linking shaders program:\n\t%s\n", log);
    return -1;
  }

  return 0;
}

static unsigned int CreateVAO(void)
{
  /* Esses arrays vão desaparecer no final da função. */
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

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Cria 2 buffers objects. Um para conter os vértices e outro para as cores dos vértices. */
  glGenBuffers(2, vbo);

  /* Carrega o vbo com os vertices e associa os atributos. */
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, BUFFER_OFFSET(0));

  /* Carrega o vbo com as cores e associa os atributos. */
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, 0, 0, BUFFER_OFFSET(0));

  /* NOTE: Ao sair, o VAO e os VBOs estarão "bounded". */

  return vao;
}


