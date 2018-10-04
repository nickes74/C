void inversion(char*);

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char chaine[81];

    printf("Entrez un texte :");
    gets(chaine);

    inversion(chaine);

    return 0;
}

void inversion(char* chaine)
{
    char chaineInv[81];
    int i=0;
    int j=0;
    int longueur=0;

    longueur=strlen(chaine);
    j=longueur-1;

    for (i=0; i<longueur; i++)
    {
        chaineInv[j]=chaine[i];
        j--;
    }

    chaineInv[longueur]=0;

    printf("\n\n%s",chaineInv);
}
