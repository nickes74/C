#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char chaine[81];
    char chaine2[81];
    int i=0;
    int j=0;

    printf("Entrez un texte : "),
    gets(chaine);

    while(chaine[i] != '\0')
    {
        if (chaine[i] != 'e')
        {
            chaine2[j]=chaine[i];
            j++;
        }
    i++;
    }
    chaine2[j]='\0';
    puts(chaine2);

    return 0;
}
