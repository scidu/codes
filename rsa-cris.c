#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char alfabeto[29] = "//ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
//int coPrimo (int e, int totiente);

//-----------  GERAR CHAVE PÚBLICA -----------------------
//______________Função que verifica se o número é primo________________________________
int primo(int p)
{
    int i;
    if (p <= 1)
        return 1;
    else
    {
        for (i = 2; i <= sqrt(p); i++)
            if (p % i == 0)
                return 1;
    }
    return 0;
}
//_____________Função que rejeita se o número não for primo______________________
int validarprimo(int p)
{
    int r;
    r = primo(p);
    while (r)
    {
        printf("Redigite um valor válido:");
        scanf("%d", &p);
        r = primo(p);
    }
    return p;
}
//________________Calcula o mdc entre dois números_______________________________
int mdc(int a, int b)
{
    if (b == 0)
        return a;
    else
        return mdc(b, a % b);
}
//____________Calcula se o totiente e o e são coprimos___________________________
int coPrimo(int e, int totiente)
{
    return mdc(e, totiente) == 1;
}
//_________________Função que calcula possiveis valores para e___________________________
void listaCoprimos(int totiente)
{
    int i, j = 10;
    printf("sugestões de 'e': ");
    for (i = 2; i < totiente; i++)
    {
        if (coPrimo(i, totiente))
        {
            printf("%d ", i);
            j--;
            if (j < 0)
                break;
        }
    }
    printf("\n");
}
//____________Função que gera a chave_____________________________________
void gerarchave()
{
    int p, q, cp1, totient, e;
    system("clear");
    printf("Digite p:");
    scanf("%d", &p);
    getchar();
    p = validarprimo(p);

    printf("Digite q:");
    scanf("%d", &q);
    getchar();
    q = validarprimo(q);

    cp1 = p * q; //Calcula a primeira chave pública

    //__Loop que rejeita se a multiplicação entre os números for menor ou igual a 27__
    while (cp1 <= 27)
    {
        printf("Obs.: Redigite dois primos tal que p*q>27\n");
        printf("Digite p:");
        scanf("%d", &p);
        getchar();
        p = validarprimo(p);
        printf("Digite q:");
        scanf("%d", &q);
        getchar();
        q = validarprimo(q);
        cp1 = p * q;
    }

    totient = (p - 1) * (q - 1);
    listaCoprimos(totient);
    printf("Escolha um e:");
    scanf("%d", &e);
    getchar();
    while (!coPrimo(e, totient))
    {
        printf("Redigite um valor para e:\n");
        scanf("%d", &e);
    }
    //________Criando um arquivo________________
    FILE *out = fopen("chavespublica.txt", "w");
    fprintf(out, "Chaves publicas: ");
    fprintf(out, "n= %d ", cp1);
    fprintf(out, "e= %d\n", e);

    fclose(out);
    printf("\nChave pública gerada com sucesso em chavepublica.txt\n");
    printf("Tecle ENTER para continuar...");
    getchar();
}

//----------------- ENCRIPTAR MENSAGEM --------------------------

//________Função que calcula a exponenciação modular_________________
int expmod(int a, int b, int n)
{
    if (b == 0)
        return 1;
    else
    {
        long long res = expmod(a, b / 2, n);
        res = (res * res) % n;
        if (b % 2 == 1)
            res = (res * a) % n;
        return (int)res;
    }
}
//________Função que encripta a mensagem_____________________________
void encriptar()
{
    system("clear");
    char texto[100];
    int cp, e, tam, i, j;
    printf("Digite um texto:\n");
    scanf("%[^\n]s", texto);
    getchar();
    printf("Digite as chave públicas:");
    scanf("%d %d", &cp, &e);
    getchar();
    tam = strlen(texto);
    FILE *out = fopen("msgcriptografada.txt", "w");
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j <= 27; j++)
        {
            if (toupper(texto[i]) == alfabeto[j])
            {
                break;
            }
        }
        fprintf(out, "%d ", expmod(j, e, cp));
    }
    fclose(out);
    printf("Mensagem encriptada com sucesso em msgcriptografada.txt\n");
    printf("Tecle ENTER para continuar...");
    getchar();
}

// ------------------ DESENCRIPTAR MENSAGEM ------------------------
int inverso(int e, int totiente)
{
    int d;
    for (d = 1; d <= totiente; d++)
        if ((d * e) % totiente == 1)
        {
            return d;
        }
}

void desencriptar()
{
    system("clear");
    int p, q, e, totiente = 0, cp1, crip, t, s, j;
    char lixo;
    printf("Digite p:\n");
    scanf("%d", &p);
    getchar();
    p = validarprimo(p);
    printf("Digite q:\n");
    scanf("%d", &q);
    getchar();
    q = validarprimo(q);
    cp1 = p * q;

    totiente = (p - 1) * (q - 1);
    printf("Digite e:\n");
    scanf("%d", &e);
    getchar();
    while (!coPrimo(e, totiente))
    {
        printf("Redigite um valor para e:\n");
        scanf("%d", &e);
        getchar();
    }

    t = inverso(e, totiente);

    FILE *out = fopen("texto.txt", "w");
    printf("Digite a mensagem a ser descriptografada: ");

    do
    {
        scanf("%d", &crip);
        s = expmod(crip, t, cp1);
        fprintf(out, "%c", alfabeto[s]);
    } while (getchar() != '\n');
    fclose(out);
    printf("Mensagem descriptografada com sucesso em texto.txt\n");
    printf("Tecle ENTER para continuar...");
    getchar();
}
int main()
{
    int opcao;
    while (1)
    {
        system("clear");
        printf("Bem vindo ao programa RSA\n");
        printf("Escolha uma opcao:\n\n");
        printf("[1] Criar chaves publicas\n");
        printf("[2] Criptografar\n");
        printf("[3] Descriptografar\n");
        printf("[0] SAIR.\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao == 1)
        {
            gerarchave();
        }
        else if (opcao == 2)
        {
            encriptar();
        }
        else if (opcao == 3)
        {
            desencriptar();
        }
        else if (opcao == 0)
        {
            system("clear");
            break;
        }
    }
    return 0;
}