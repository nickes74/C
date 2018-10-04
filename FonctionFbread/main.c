#include <stdio.h>
#include <stdlib.h>

void fbread(VERSEMENT,VERSEMENT*,int*);

typedef struct
{
    char nosect[3];
    char norep[4];
    char nocli[5];
    char nofac[6];
    double mont;
    char codpays[3];
} VERSEMENT;

int main()
{
    VERSEMENT versement;
    VERSEMENT* vers;
    FILE* fichierVersement;
    int i=0;
    int compteur=0;
    int div;
    int mod;

    fichierVersement = fopen("R:\\C\\fichiers\\versements","rb");

    if (fichierVersement == NULL)
    {
        printf(" *** ERREUR OUVERTURE FICHIER DES VERSEMENTS *** ");
        exit(0);
    }


    fclose(fichierVersement);

    return 0;
}


void fbread (VERSEMENT versement,VERSEMENT* vers, int* div)
{
     while (!feof (fichierVersement))
    {
        fread(&versement,sizeof(VERSEMENT),1,fichierVersement);

        if (versement.nosect != 0)
        {
            compteur++;
        }
    }

    div = compteur/4;
    mod = compteur%4;

    printf("il y a %d fichiers donc %d fbread et restera : %d fichiers\n",compteur,div,mod);

    if (div != 0)
    {
        fread(vers,sizeof(VERSEMENT),4,fichierVersement);
        div--;

        return 0;
    }
    else
    {
       fread(vers,sizeof(VERSEMENT),mod,fichierVersement);

       return 0;
    }

}
