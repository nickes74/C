int comptage (char*);

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char chaine[81];
    int resultat;

    printf("Entrez un texte : ");
    gets(chaine);

    resultat=comptage(chaine);

    printf("\nIl y a %d 'e' dans le texte", resultat);

    return 0;
}


int comptage(char* chaine)
{
    int compte=0;
    int longueur;
    int i=0;

    longueur=strlen(chaine);

    //printf("%s",ligne);

    for (i=0; i<longueur; i++)
    {
        if (chaine[i]=='e')
        {
            compte++;
        }
    }

    return compte;
}
