#include <stdio.h>
#include <jni.h>

/* 
   ATENÇÃO: O nome da função exportada tem que seguir o padrão:

            Java_#class_#function.

            Onde: #class é exatamente o nome da classe.
                  #function é exatamente o nome da função nativa.

            A documentação do JNI explica a nomenclatura... (é bom ver!).

            A lista de parâmetros sempre tem que ser:
            (JNIEnv *env, jobject obj, ...)

            Onde os parâmetros adicionais (depois de 'obj') são
            dos tipos definidos em jni.h.

            Veja HelloWorld.java. 
*/
JNIEXPORT void JNICALL Java_HelloWorld_print(JNIEnv *env, jobject obj, jstring javaString)
{
  const char *str;

  str = (*env)->GetStringUTFChars(env, javaString, 0);

  printf("%s\n", str);
  (*env)->ReleaseStringUTFChars(env, javaString, str);
}
