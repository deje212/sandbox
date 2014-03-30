/* Works only if compiled with gcc using libc6. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <regex.h>

typedef struct {
  unsigned addr;
  unsigned cidr;
} CIDR;

#define IP_REGEX "^([1-2]*[0-9]{1,2})" \
                 "(\\.[1-2]*[0-9]{1,2}){0,1}" \
                 "(\\.[1-2]*[0-9]{1,2}){0,1}" \
                 "(\\.[1-2]*[0-9]{1,2}){0,1}" \
                 "(/[0-9]{1,2}){0,1}$"

int get_ip_and_cidr(char const * const addr, CIDR *cidr_ptr)
{
  regex_t re;
  regmatch_t rm[6];
  unsigned matches[5];
  int i, len;
  char *t;

  cidr_ptr->addr = cidr_ptr->cidr = 0;

  /* Try to compile the regular expression. */
  if (regcomp(&re, IP_REGEX, REG_EXTENDED))
    return 0;

  /* Try to execute regex against the addr string. */
  if (regexec(&re, addr, 6, rm, 0))
  {
    regfree(&re);
    return 0;
  }

  /* Allocate enough space for temporary string. */
  if ((t = (char *)malloc(strlen(addr)+1)) == NULL)
  {
    perror("Cannot allocate temporary string");
    abort();
  }

  /* Convert IP octects matches. */
  len = rm[1].rm_eo - rm[1].rm_so;
  strncpy(t, addr+rm[1].rm_so, len); 
  t[len] = 0;
  matches[0] = atoi(t);

  for (i = 2; i <= 4; i++)
  {
    len = rm[i].rm_eo - rm[i].rm_so - 1;
    if (len > 0)
    {
      strncpy(t, addr+rm[i].rm_so+1, len); 
      t[len] = 0;
      matches[i-1] = atoi(t);
    }
    else
      matches[i-1] = 0;
  }

  /* Convert cidr match. */
  len = rm[5].rm_eo - rm[5].rm_so - 1;
  if (len > 0)
  {
    strncpy(t, addr+rm[5].rm_so+1, len); 
    t[len] = 0;
    if ((matches[4] = atoi(t)) == 0)
    {
      /* if cidr is actually '0', then it is an error! */
      free(t);
      regfree(&re);
      return 0;
    }
  }
  else
    matches[4] = 32;

  /* We don't need 't' string anymore. */
  free(t);

  /* Validate ip octects */
  for (i = 0; i < 4; i++)
    if (matches[i] > 255)
    {
      regfree(&re);
      return 0;
    }

  /* Validate cidr. */
  if (matches[4] > 32)
  {
    regfree(&re);
    return 0;
  }

  /* Prepare CIDR structure */
  cidr_ptr->cidr = matches[4];
  cidr_ptr->addr = (((matches[3] & 0xff))       |
                    ((matches[2] & 0xff) << 8)  |
                    ((matches[1] & 0xff) << 16) |
                    ((matches[0] & 0xff) << 24)) &
                      (0xffffffff << (32 - cidr_ptr->cidr));

  regfree(&re);

  return 1;
}

int main(int argc, char *argv[])
{
  CIDR cidr;

  if (argc != 2)
  {
    puts("Error: Usage ipcidr_regex <ip>[/cidr]\n");
    return EXIT_FAILURE;
  }

  if (get_ip_and_cidr(argv[1], &cidr))
    printf("Found: 0x%08X/%d\n", cidr.addr, cidr.cidr);
  else
  {
    puts("Error on parameter.");
    return EXIT_FAILURE;
  }

  return 0;
}
