#include <fcntl.h>
#include <unistd.h>
#include "random.h"

/* Lê 'size' "long ints" de /dev/urandom. */
/* Retorna -1 se erro, 0 se ok */
int read_random_array(void *data, size_t size)
{
  int fd;
  size_t len;
  long int *p;

  fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0)
    return -1;

  p = data;
  for (len = 0; len < size; len++)
    if (read(fd, p++, sizeof(long int)) < 0)
    {
      close(fd);
      return -1;
    }

  close(fd);

  return 0;  
}
