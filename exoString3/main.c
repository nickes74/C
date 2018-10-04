#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char chaine[81];
    char chaineInv[81];
    int longueur=0;
    int indexe=0;
    int indexe2=0;

    printf("entrez un texte :");
    gets(chaine);

    longueur=strlen(chaine);
    indexe2=longueur-1;

    for (indexe = 0; indexe<longueur; indexe++)
    {
        chaineInv[indexe]=chaine[indexe2];
        indexe2--;
    }

    chaineInv[indexe]=0;
    puts(chaineInv);

    return 0;
}
