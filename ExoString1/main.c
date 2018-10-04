#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char chaine[81];
    int compteur = 0;
    int indexe=0;


    printf("entrez un texte :");
    gets(chaine);

    while (chaine[indexe] != '\0')
   {
        if (chaine[indexe] == 'e')
        {
            compteur++;
        }
        indexe++;
   }

    printf("\n\nNombre de e: %d",compteur);

    return 0;
}
