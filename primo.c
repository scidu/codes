#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// FUNÇÃO QUE VERIFICA SE É PRIMO
bool is_prime(int n)
{
    int i;
    if (n == 1 || n == 0)
    {
        return false;
    }
    else
    {
        for (i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}

int main()
{
    int n;

    scanf("%d", &n);

    if (is_prime(n))
    {
        printf("1");
    }
    else
    {
        printf("0");
    }
    return 0;
}