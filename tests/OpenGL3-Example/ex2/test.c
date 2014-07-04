/* ==================================================
   example.c

   Código básico de uso de VBOs, VAOs e Shaders.
   ================================================== */
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <sys/time.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glfw.h>

/* Esta é a resolução que estou usando. */
#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

int finished = 0;

/* Vertex Array Object, Vertex Buffer Object e 
   Program Object para OpenGL. */
GLuint vao, vbo, prgo;

/* Protótipos. */
void initGLFW(void);
void initGL(void);
void initModel(void);
void initShaders(void);
void destroyGLFW(void);
void drawScene(void);
void processEvents(void);

int main(int argc, char *argv[])
{
  initGLFW();
  initGL();
  initShaders();
  initModel();

  while (!finished)
  {
    drawScene();
    processEvents();
    glfwSwapBuffers();
  }

  destroyGLFW();

  return 0;
}

/* Tratamento de teclado, mouse e joystick aqui. */
void processEvents(void)
{
  glfwPollEvents();
  if (glfwGetKey(GLFW_KEY_ESC))
    finished = 1;
}

/* Inicializa o GLFW. */
void initGLFW(void)
{
  if (!glfwInit())
  {
    fprintf(stderr, "Error initializing GLFW.\n");
    exit(1);
  }

  glfwDisable( GLFW_AUTO_POLL_EVENTS );

  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 4 );
  glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 3 );

  if (glfwExtensionSupported( "GLX_ARB_create_context_profile" ))
    glfwOpenWindowHint( GLFW_OPENGL_PROFILE, 
                        GLFW_OPENGL_CORE_PROFILE );

  /* Full Screen Anti Aliasing */
  glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );  

  if (!glfwOpenWindow( WINDOW_WIDTH, WINDOW_HEIGHT, 
                       8, 8, 8, 8, 
                       24, 
                       0, 
                       GLFW_WINDOW ))
  {
    glfwTerminate();
    fprintf(stderr, "Cannot create Window.\n");
    exit(1);
  }

  glfwDisable( GLFW_MOUSE_CURSOR );

  glfwSetWindowTitle( "GLSL Test" );
}

void destroyGLFW(void)
{
  glfwTerminate();
}

void initGL(void)
{
  glViewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );

  glClearColor( 0, 0, 0, 1 );
  glClearDepth( 1.0f );

  glFrontFace( GL_CCW );
  glCullFace( GL_BACK );
  glEnable( GL_CULL_FACE );

  glDepthFunc( GL_LESS );
  glEnable( GL_DEPTH_TEST );
}

void initModel(void)
{
  struct tris_s {
    float pos[3];
    float color[3];
  };

  /* Pra ser 'chato', esse triângulo é equilatero. */
  struct tris_s tris[] = {
    {{ 0.0f,  M_SQRT1_2, -1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-0.5f, -0.5f,      -1.0f}, {0.0f, 1.0f, 0.0f}},
    {{ 0.5f, -0.5f,      -1.0f}, {0.0f, 0.0f, 1.0f}}
  };

  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );

  glGenBuffers( 1, &vbo );
  glBindBuffer( GL_ARRAY_BUFFER, vbo );
  glBufferData( GL_ARRAY_BUFFER, sizeof(tris), tris, GL_STATIC_DRAW );

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(struct tris_s), (void *)offsetof(struct tris_s, pos) );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof(struct tris_s), (void *)offsetof(struct tris_s, color) );

  glEnableVertexAttribArray( 0 );
  glEnableVertexAttribArray( 1 );

  glBindVertexArray( 0 );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

static char *LoadTextFile(const char *filename)
{
  char *buffer;
  FILE *fin;
  long size;
  jmp_buf jb;

  if ((fin = fopen(filename, "rb")) == NULL)
    return NULL;

  // Tratamento de erro.
  if (setjmp(jb))
  {
    fclose(fin);
    return NULL;
  }

  // Pega o tamanho do arquivo.
  fseek(fin, 0L, SEEK_END);
  if ((size = ftell(fin)) < 0)
    longjmp(jb, 1);
  fseek(fin, 0L, SEEK_SET);

  // Aloca espaço para o buffer.
  if ((buffer = malloc(size + 1)) == NULL)
    longjmp(jb, 1);

  // Tenta ler o arquivo inteiro.
  if (fread(buffer, size, 1, fin) < 1)
  {
    free(buffer);
    longjmp(jb, 1);
  }

  // Certifica-se que a string termina com 0.
  buffer[size] = '\0';

  fclose(fin);
  return buffer;
}

static GLuint LoadAndCompileShader(const char *filename, GLenum shadertype)
{
  GLuint shobj;

  // Tenta criar um shader object.
  if ((shobj = glCreateShader( shadertype )) != 0)
  {
    GLint status;
    GLint len;
    char *src;

    // Tenta carregar o código do shader.
    if ((src = LoadTextFile(filename)) == NULL)
    {
      glDeleteShader( shobj );
      return 0;
    }
    len = strlen(src);

    // Insere o código no shader object e tenta compilá-lo.
    glShaderSource( shobj, 1, &src, &len );
    glCompileShader( shobj );

    // Não precisamos mais do código fonte!
    free(src);

    // Verifica se a compilação foi bem sucedida.
    glGetShaderiv( shobj, GL_COMPILE_STATUS, &status );
    if (status == GL_FALSE)
    {
      GLint logsize;
      char *log;

      glGetShaderiv( shobj, GL_INFO_LOG_LENGTH, &logsize );
      if ((log = malloc(logsize+1)) != NULL)
      {
        glGetShaderInfoLog( shobj, logsize, &len, log );
        log[len] = '\0';
        fprintf(stderr, "%s: %s\n", filename, log);
        free(log);
      }

      glDeleteShader( shobj );
      return 0;
    }
  }
  
  return shobj;
}

// Esta estrutura será usada para montar a tabela de
// shaders que usaremos para montar o programa.
struct shader_info_s {
  char *filename;
  GLenum shadertype;
  GLuint shobj;
};

// Rotina auxiliar local: Apaga os shaders objects da lista.
static void DeleteAllShadersOnList(GLuint prgobj, struct shader_info_s *shinf_ptr)
{
  for (;shinf_ptr->filename; shinf_ptr++)
    if (shinf_ptr->shobj)
    {
      // Só 'destaca' os shaders objects se um program object for fornecido.
      if (prgobj)
        glDetachShader( prgobj, shinf_ptr->shobj );
      glDeleteShader( shinf_ptr->shobj );
      shinf_ptr->shobj = 0;
    }
}

static GLuint CreateShadersProgram(struct shader_info_s *shinf_ptr)
{
  GLuint prgobj;
  struct shader_info_s *sptr = shinf_ptr;

  // Tenta carregar e compilar todos os shaders da lista.
  for (sptr = shinf_ptr; sptr->filename; sptr++)
    if ((sptr->shobj = LoadAndCompileShader(sptr->filename, sptr->shadertype)) == 0)
    {
      DeleteAllShadersOnList( 0, shinf_ptr );
      return 0;
    }

  // Tenta criar um programa.
  if ((prgobj = glCreateProgram()) != 0)
  {
    GLint status;

    // Associa os shaders objects ao programa e os linka.
    for (sptr = shinf_ptr; sptr->shobj; sptr++)
      glAttachShader( prgobj, sptr->shobj );
    glLinkProgram( prgobj );

    // Depois de linkados, não precisamos mais dos shaders objects.
    DeleteAllShadersOnList( prgobj, shinf_ptr );

    // Verifica se a linkagem foi bem sucedida.
    glGetProgramiv( prgobj, GL_LINK_STATUS, &status );
    if (status == GL_FALSE)
    {
      GLint logsize, len;
      char *log;

      glGetProgramiv( prgobj, GL_INFO_LOG_LENGTH, &logsize );
      if ((log = malloc(logsize + 1)) != NULL)
      {
        glGetProgramInfoLog( prgobj, logsize, &len, log );
        log[len] = 0;
        fprintf(stderr, "Link Error: %s\n", log);
        free(log);
      }

      // Já que temos um erro, livramo-nos do programa 'vazio'.
      glDeleteProgram( prgobj );

      return 0;
    }
  }

  return prgobj;
}

void initShaders(void)
{
  struct shader_info_s shaders[] = {
    { "test.vert", GL_VERTEX_SHADER, 0 },
    { "test.frag", GL_FRAGMENT_SHADER, 0 },
    { NULL, 0, 0 }
  };

  if ((prgo = CreateShadersProgram( shaders )) == 0)
  {
    fprintf(stderr, "Error creating shaders.\n");
    exit(1);
  }
}

void drawScene(void)
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glBindBuffer( GL_ARRAY_BUFFER, vbo );
  glBindVertexArray( vao );

  glUseProgram( prgo );
  glDrawArrays( GL_TRIANGLES, 0, 3 );
  glUseProgram( 0 );

  glBindVertexArray( 0 );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
}
