#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void)
{
  void *handle;
  char *error;
  void (*fptr)(int);

  handle = dlopen("./libmodule.so", RTLD_NOW | RTLD_GLOBAL);
  if (handle == 0)
  {
    fprintf(stderr, "Cannot find libmodule.so!");
    exit(1);
  }   

  dlerror();  /* Clear any errors */

  fptr = dlsym(handle, "MyFunc");
  if ((error = dlerror()) != NULL)
  {
    fprintf(stderr, "Error finding symbol MyFunc: %s\n", error);
    dlclose(handle);
    exit(1);
  }

  fptr(10);

  dlclose(handle);

  return 0;
}
