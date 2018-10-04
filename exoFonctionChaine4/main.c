void positions(char*);

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char chaine[81];

    printf("Entrez un texte :");
    gets(chaine);

    positions(chaine);


    return 0;

}

void positions(char* chaine)
    {
    int i=0;
    int j=0;
    int longueur=0;

    longueur=strlen(chaine);

    j=longueur-1;

    if (longueur == 0)
    {
        printf("\nChaine saisie vide");
    }
    else
    {
        while(chaine[i]==' ' && i<longueur)
        {
            i++;
        }
        if (i == longueur)
        {
            printf("\nchaine uniquement en caracteres blancs");
        }
        else
        {
            while(chaine[j]==' ' )
            {
                j--;
            }
        }
        printf("\nPremier caractere non blanc en position : %d",i+1);
        printf("\nDernier caractere non blanc en position : %d",j);
    }

    }

