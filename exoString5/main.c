#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char chaine[81];
    char chaine2[81];
    char chainefinale[81];
    int position=0;
    int longueur=0;
    int longueur2=0;
    int i=0;
    int j=0;
    int k=0;

    printf("Entrez un texte : ");
    gets(chaine);

    longueur=strlen(chaine);

    printf("Entrez un 2e texte : ");
    gets(chaine2);

    longueur2=strlen(chaine2);

    printf("\nEntrez une position :");
    scanf("%d", &position);

    position=position-1;

    for (i=0; i<position; i++)
    {
        chainefinale[i]=chaine[i];
    }

    k=i;

    for (i=position; i<position+longueur2; i++)
    {
        chainefinale[i]=chaine2[j];
        j++;
    }


    for (i=position+longueur2; i<longueur2+longueur; i++)
    {
        chainefinale[i]=chaine[k];
        k++;
    }

    chainefinale[i]=0;

    printf("\nChaine finale : \n");
    puts(chainefinale);


    return 0;
}
