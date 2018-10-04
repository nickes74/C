
#include <stdio.h>
#include <stdlib.h>

#include "chaine.h"


/* ====================================================== */
/* Fonction de comptage de lettre dans le texte (ici 'e') */
/* ====================================================== */
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

/* ========================================================= */
/* Fonction de suppression de lettre dans le texte (ici 'e') */
/* ========================================================= */

void suppressionE(char* chaine)
{
    char chaineSansE[81];
    int longueur;
    int i;
    int j=0;

    longueur=strlen(chaine);

    for (i=0; i<longueur; i++)
    {
        if (chaine[i]!='e')
        {
            chaineSansE[j]=chaine[i];
            j++;
        }
    }
    chaineSansE[j]=0;
    printf("\n\nChaine sans 'e' : %s",chaineSansE);
}

/* ================================================================ */
/* Fonction d'inversion du texte avec untilistation d'une 2e chaine */
/* ================================================================ */

void inversion(char* chaine)
{
    char chaineInv[81];
    int i=0;
    int j=0;
    int longueur=0;

    longueur=strlen(chaine);

    j=longueur-1;

    for (i=0; i<longueur; i++)
    {
        chaineInv[j]=chaine[i];
        j--;
    }

    chaineInv[longueur]=0;

    printf("\n\nChaine inversee : %s",chaineInv);
}

/* ================================================================================== */
/* Fonction d'information du positionnement du premier et dernier caractere non blanc */
/* ================================================================================== */

void positions(char* chaine)
    {
    int i=0;
    int j=0;
    int longueur=0;

    longueur=strlen(chaine);

    j=longueur;

    if (longueur == 0)
    {
        printf("\nChaine saisie vide");
    }
    else
    {
        while(chaine[i]==' ' && i<longueur)
        {
            i++;
        }
        if (i == longueur)
        {
            printf("\nchaine uniquement en caracteres blancs");
        }
        else
        {
            while(chaine[j]==' ' )
            {
                j--;
            }
        }
        printf("\n\nPremier caractere non blanc en position : %d",i+1);
        printf("\nDernier caractere non blanc en position : %d",j);
    }

    }

/* ===================================================================================== */
/* Fonction d'insertion d'un sous texte dans le premier avec comblage de blanc si besoin */
/* ===================================================================================== */


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

    printf("\nChaine finale : ");
    puts(chaine);

    return 0;
}

