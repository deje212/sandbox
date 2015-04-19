#include <stdio.h>
#include <string.h>

char *data = "fred";

void main(int argc, char *argv[])
{
  FILE *f;
  int fd;

  if (argc != 2) 
  { 
    fprintf(stderr, "Uso: sparse <filename>\n"); 
    return; 
  }

  if ((f  = fopen(argv[1], "w")) == NULL)
  {
    fprintf(stderr, "Error creating sparse file '%s'.\n", argv[1]);
    return;
  }

  fwrite(data, strlen(data), 1, f);

  /* Salta para a posição 10000 do arquivo. */
  fseek(f, 10000, SEEK_SET);

  fwrite(data, strlen(data), 1, f);

  fclose(f);
}

