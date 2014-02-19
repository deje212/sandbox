#include <fcntl.h>
#include <unistd.h>
#include "random.h"

/* Lê 'size' "long ints" de /dev/urandom. */
/* Retorna -1 se erro, 0 se ok */
int read_random_array(void *data, size_t size)
{
  int fd, ret;

  if (size == 0)
    return -1;

  fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0)
    return -1;

  ret = 0;
  if (read(fd, data, size) < 0)
    ret = -1;

  fclose(fd);

  return ret;
}
