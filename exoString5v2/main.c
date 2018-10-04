#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char chaine[81];
    char sousChaine[81];
    char chaineBlanc[81];
    int position=0;
    int longueur=0;
    int longueur2=0;
    int i=0;


    printf("Entrez un texte : ");
    gets(chaine);

    longueur=strlen(chaine);

    printf("Entrez un 2e texte : ");
    gets(sousChaine);

    longueur2=strlen(sousChaine);

    printf("\nEntrez une position :");
    scanf("%d", &position);

    position=position-1;

    if (position<=0)
    {
        printf("\nrecommencez");
    }
    else if (position>longueur || longueur2+position>longueur)
    {
        for (i=0; i<(position+longueur2)-longueur;i++)
        {
            chaineBlanc[i]=' ';
        }
        chaineBlanc[i]=0;

        strcat(chaine,chaineBlanc);
        strncpy (chaine+position,sousChaine,longueur2);

    }
    else
    {
    strncpy (chaine+position,sousChaine,longueur2);
    }

    printf("\nChaine finale : \n");
    puts(chaine);

    return 0;
}
