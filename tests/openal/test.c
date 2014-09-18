// Ainda não está funcionando.
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

int main(int argc, char *argv[])
{
  ALCdevice *device;
  ALCcontext *context;
  ALuint source;
  ALuint buffer;
  ALenum source_state;
  ALfloat listenerOrientation[] = { 0, 0, -1, 0, 1, 0 };
  ALfloat positions[] = { 0, 0, 1,
                          0, 0, -1,
                          1, 0, 0,
                         -1, 0, 0 };
  int i;

  // FIXME: alutInit creates an initial context?!
  if (alutInitWithoutContext(&argc, argv) == AL_FALSE)
  {
    fprintf(stderr, "Error initializing ALUT.\n");
    return 1;
  }

  if ((device = alcOpenDevice(NULL)) == NULL)
  {
    fprintf(stderr, "Erro inicializando dispositivo.\n");
    return 1;
  }
  
  context = alcCreateContext(device, NULL);
  if ((context == NULL) || (alcMakeContextCurrent(context) == AL_FALSE))
  {
    fprintf(stderr, "Erro ajustando contexto.\n");
    alcCloseDevice(device);
    return 1;
  }

  // Ajusta o listener.
  alListener3f(AL_POSITION, 0, 0, 0);
  alListenerfv(AL_ORIENTATION, listenerOrientation);

  // Ajusta source.
  alGenSources(1, &source);

  // Carrega wave (deprecated).
  if ((buffer = alutCreateBufferFromFile("./wilhelm.wav")) == 0)
  {
    alDeleteSources(1, &source);
    alcMakeContextCurrent(NULL);
    alcCloseDevice(device);
    fprintf(stderr, "Error creating buffer.\n");
    return 1;
  }

  // Liga buffer ao source.
  alSourcei(source, AL_BUFFER, buffer);

  /* Tenta tocar nas 4 posições. */
  for (i = 0; i < 4; i++)
  {
    printf("Playing sample at position (%.1f, %.1f, %.1f)\n",
      positions[3*i], positions[3*i+1], positions[3*i+2]);

    alSourcefv(source, AL_POSITION, &positions[3*i]);

    alSourcePlay(source);

    do
    {
      alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    } while (source_state == AL_PLAYING);

    sleep(1);
  }

  alSourcei(source, AL_BUFFER, 0);
  alDeleteBuffers(1, &buffer);
  alDeleteSources(1, &source);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
  alutExit();

  return 0;
}
