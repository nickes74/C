#include <stdio.h>
#include <stdlib.h>

int main()
{
    char chaine[81];
    int indexe=0;
    int longueur=0;

    printf("entrez un texte :");
    gets(chaine);

    longueur=strlen(chaine);

    printf("\nAdresse de debut absolu : %p",chaine);

    while (chaine[indexe] !=0 && chaine[indexe]==' ')
    {
        indexe++;
    }


    printf("\nAdresse de debut apres caracteres blancs : %p", &chaine[indexe]);

    printf("\nAdresse dernier caratere : %p", &chaine[longueur]);

    return 0;
}
