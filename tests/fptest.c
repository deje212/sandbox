#include <float.h>
#include <stdio.h>

/* Imprimindo a variável contendo o menor valor comparável a zero */
int main(void)
{
    int i;
    float feps, feps1;

    /* A variável feps irá conter a precisão da máquina */

    i = 0;
    feps = 1.0f;
    feps1 = 0.0f;
    do  {
        feps /= 2.0f;
        feps1 = feps + 1.0f;
        printf("%3dª reduzida - EPSILON = %-10.10g \n", ++i, feps);
    } while ( feps1 > 1.0f);

    printf("A máquina pensa que '%-10.10g' é igual a zero\n", feps);

    return 0;
}
