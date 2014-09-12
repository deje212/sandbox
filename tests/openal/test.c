// Ainda não está funcionando.
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
  ALboolean enumeration;
  ALsizei size, freq;
  ALenum format;
  ALenum source_state;
  ALvoid *data;
  ALboolean loop = AL_FALSE;
  ALfloat listenerOrientation[] = { 0, 0, 1, 0, 1, 0 };

  if ((device = alcOpenDevice(NULL)) == NULL)
  {
    fprintf(stderr, "Erro inicializando dispositivo.\n");
    return 1;
  }
  
  enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
  if (enumeration != AL_FALSE)
    printf("Device Specifiers: %s\n", alcGetString(NULL, ALC_DEVICE_SPECIFIER));

  context = alcCreateContext(device, NULL);
  if (!context && !alcMakeContextCurrent(context))
  {
    fprintf(stderr, "Erro ajustando contexto.\n");
    alcCloseDevice(device);
    return 1;
  }

  // Ajusta o listener.
  alListener3f(AL_POSITION, 0, 0, 1);
  alListener3f(AL_VELOCITY, 0, 0, 0);
  alListenerfv(AL_ORIENTATION, listenerOrientation);

  // Ajusta source.
  alGenSources(1, &source);
  alSourcef(source, AL_PITCH, 1);
  alSourcef(source, AL_GAIN, 1);
  alSource3f(source, AL_POSITION, 0, 0, 0);
  alSource3f(source, AL_VELOCITY, 0, 0, 0);
  alSourcef(source, AL_LOOPING, AL_FALSE);

  // Cria o buffer.
  alGenBuffers(1, &buffer);

  // Carrega wave (deprecated).
  alutLoadWAVFile("./wilhelm.wav", &format, &data, &size, &freq, &loop);
  alBufferData(buffer, format, data, size, freq);

  // Liga buffer ao source.
  alSourcei(source, AL_BUFFER, buffer);

  alSourcePlay(source);

  alGetSourcei(source, AL_SOURCE_STATE, &source_state);
  // check for errors
  while (source_state == AL_PLAYING)
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);

  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  return 0;
}
