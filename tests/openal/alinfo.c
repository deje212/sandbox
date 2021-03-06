// Compilar com:
//    gcc -O3 -o alinfo alinfo.c -lopenal
//
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <AL/al.h>
#include <AL/alc.h>

int main(int argc, char *argv[])
{
  ALCdevice *device;
  ALCcontext *context;
  const char *version, *renderer, *vendor, *extensions;
  char *e, *p;

  if ((device = alcOpenDevice(NULL)) == NULL)
  {
    fprintf(stderr, "ERRO abrindo dispositivo.\n");
    return 1;
  }

  if ((context = alcCreateContext(device, NULL)) == NULL)
  {
    alcCloseDevice(device);
    fprintf(stderr, "ERRO ao criar contexto default.\n");
    return 1;
  }

  alcMakeContextCurrent(context);

  version = alGetString(AL_VERSION);
  renderer = alGetString(AL_RENDERER);
  vendor = alGetString(AL_VENDOR);
  extensions = alGetString(AL_EXTENSIONS);

  printf("Version: %s\n"
         "Renderer: %s\n"
         "Vendor: %s\n"
         "Extensions:\n",
         version, renderer, vendor);

  e = strdup(extensions);

  p = strtok(e, " ");
  while (p)
  {
    printf("  %s\n", p);
    p = strtok(NULL, " ");
  }

  free(e);

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  return 0;
}
