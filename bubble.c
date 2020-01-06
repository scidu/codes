#include <stdio.h>

int main()
{
    int array[100];
    int i, i2, aux;

    for (i = 0; i < 10; i++)
    {
        scanf("%d", &array[i]);
    }

    for (i = 0; i < 10; i++)
    {
        for (i2 = i + 1; i2 < 10; i2++)
        {
            if (array[i] > array[i2])
            {
                aux = array[i];
                array[i] = array[i2];
                array[i2] = aux;
            }
        }
    }

    printf("Ordenado:\n");

    for (i = 0; i < 10; i++)
    {
        printf("%d\n", array[i]);
    }

    return 0;
}
