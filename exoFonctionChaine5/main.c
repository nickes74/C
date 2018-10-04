void insertionChaine(char*,char*,int);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char chaine[81];
    char chaine2[81];
    int position=0;


    printf("Entrez un texte : ");
    gets(chaine);



    printf("Entrez un sous texte : ");
    gets(chaine2);


    printf("\nEntrez une position :");
    scanf("%d", &position);

    insertionChaine(chaine,chaine2,position);


    return 0;
}


void insertionChaine(char* chaine,char* chaine2,int position)
{
    char chaineBlanc[81];
    int longueur=0;
    int longueur2=0;
    int i=0;


    longueur=strlen(chaine);

    longueur2=strlen(chaine2);

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
        strncpy (chaine+position,chaine2,longueur2);

    }
    else
    {
    strncpy (chaine+position,chaine2,longueur2);
    }

    printf("\nChaine finale : \n");
    puts(chaine);

    return 0;
}
