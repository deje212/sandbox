#ifndef __STRING2_H_INCLUDED__
#define __STRING2_H_INCLUDED__

char *strncpy_z(char* dest, const char* src, size_t size);
int   strcpy_range(char* dest, const char* src, int from, int to);

#endif
