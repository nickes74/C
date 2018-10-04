#include <stdio.h>
#include <stdlib.h>

#include "..\..\utilitaires\entetes\chaines.h"

int main()
{
  char chaine[81]="";
  char result[81];
  double nombre,r;
  char sousChaine[]="fumier";
  int resultat=0;

    remplirChaine(chaine,'.',6,19);
    remplirChaine(chaine,'*',0,8);
    remplirChaine(chaine,'-',25,28);

    puts(chaine);

    printf("\nEntrez un reel: ");
    scanf("%lf",&nombre);

    doubleChaine(nombre,3,result);
    puts (result);

    remplirChaine(chaine,' ',0,80);
    placeSousChaine(chaine,result,19,'d');
    placeSousChaine(chaine,sousChaine,10,'g');
    puts(chaine);

    printf("\nSaisissez une chaine: ");
    gets(chaine);

    chaineDouble(chaine,result);
    puts(result);

    printf("\nEntrez un reel: ");
    gets(chaine);

    resultat=chaineDouble(chaine,&r);
    if(resultat==1)
    {
        printf("\nerreur\n");
    }
    else
    {
        printf("%lf",r);
    }

    return 0;
}
