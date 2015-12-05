#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int exec_prog(const char **argv)
{
  pid_t   pid;
  int     status;

  pid = fork();
  if (pid == 0)
  {
    if (execve(argv[0], (char **)argv , NULL) == -1)
      return -1;

    if (waitpid(pid , &status , 0) == -1)
        return -1;

    return WEXITSTATUS(status);
  }

  /* O processo filho jamais chegará aqui! */
  return -1;
}
