void suppressionE(char*);

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char chaine[81];

    printf("Entrez un texte :");
    gets(chaine);

    suppressionE(chaine);

    return 0;
}


void suppressionE(char* chaine)
{
    char chaineSansE[81];
    int longueur;
    int i;
    int j=0;

    longueur=strlen(chaine);

    for (i=0; i<longueur; i++)
    {
        if (chaine[i]!='e')
        {
            chaineSansE[j]=chaine[i];
            j++;
        }
    }

    printf("\n\n%s",chaineSansE);
}
