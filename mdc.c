#include <stdio.h>

int mdc(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return mdc(b, a % b);
    }
}

int main()
{
    int a = 25, b = 12, resultado;
    resultado = mdc(a, b);
    printf("%d", resultado);
    return 0;
}