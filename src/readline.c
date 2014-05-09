#include <stdio.h>
#include <string.h>

/* ppstr is a pointer to a char* (string)! */
char *freadline(FILE *f, char *buffer, size_t max_line_size)
{
  char *cp;

  if ((cp = fgets(buffer, max_line_size, f)) != NULL)
  {
    char *tmpcp;

    cp += strspn(buffer, " \t\r");

    if ((tmpcp = strchr(cp, '\n')) != NULL)
      *tmpcp = '\0';
  }

  return cp;
}

