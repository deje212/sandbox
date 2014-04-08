#include <stdio.h>
#include <jni.h>

JNIEXPORT void JNICALL Java_HelloWorld_print(JNIEnv *env, jobject obj)
{
  printf("Hello, world!\n");
}
