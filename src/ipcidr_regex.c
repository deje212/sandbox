/* Works only if compiled with gcc using libc6. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <regex.h>

#define MATCH(s)        ((s).rm_so >= 0)
#define MATCH_LENGTH(s) ((s).rm_eo - (s).rm_so)
#define COPY_SUBSTRING(d, s, len) { \
  strncpy((d), (s), (len)); \
  *((d) + (len)) = 0; \
}

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
  int i, len, bits;
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
  t = strdup(addr);
  if (t  == NULL)
  {
    perror("Cannot allocate temporary string");
    abort();
  }

  /* Convert IP octects matches. */
  if (MATCH(rm[1]))
  {
    len = MATCH_LENGTH(rm[1]);
    COPY_SUBSTRING(t, addr+rm[1].rm_so, len);
    matches[0] = atoi(t);
  }
  else  
    matches[0] = 0;

  bits = 32;
  for (i = 2; i <= 4; i++)
  {
    if (MATCH(rm[i]))
    {
      len = MATCH_LENGTH(rm[i]) - 1;
      COPY_SUBSTRING(t, addr + rm[i].rm_so + 1, len);
      matches[i-1] = atoi(t);
    }
    else
    {
      matches[i-1] = 0;
      bits -= 8;
    }
  }

  /* Convert cidr match. */
  if (MATCH(rm[5]))
  {
    len = MATCH_LENGTH(rm[5]) - 1;
    COPY_SUBSTRING(t, addr + rm[5].rm_so + 1, len);

    if ((matches[4] = atoi(t)) == 0)
    {
      /* if cidr is actually '0', then it is an error! */
      free(t);
      regfree(&re);
      return 0;
    }
  }
  else
    matches[4] = bits;

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
  cidr_ptr->addr = ( matches[3]          |
                    (matches[2]   << 8)  |
                    (matches[1]   << 16) |
                    (matches[0]   << 24) ) &
                      (0xffffffffUL << (32 - cidr_ptr->cidr));

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
