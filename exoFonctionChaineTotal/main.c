

#include <stdio.h>
#include <stdlib.h>

#include "chaine.h"

int main()
{
    char chaine[81];
    char chaine2[81];
    int position=0;
    int resultat;

    printf("Entrez un texte : ");
    gets(chaine);

    resultat=comptage(chaine);

    printf("\nIl y a %d 'e' dans le texte", resultat);

    suppressionE(chaine);

    inversion(chaine);

    positions(chaine);

    printf("\n\nEntrez un sous texte : ");
    gets(chaine2);


    printf("\nEntrez une position :");
    scanf("%d", &position);

    insertionChaine(chaine,chaine2,position);


    return 0;
}
