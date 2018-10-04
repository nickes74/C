#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "R:\C\utilitaires\entetes\chaines.h"

typedef struct
{
    char noCli[5];
    char dateFac[11];
    char noProd[5];
    int quantite;
    float prixHT;
} VENTE;

typedef struct
{
    float quinz1[7];
//    char libMois[13];
    float totalMois;
    float quinz2[7];
} MOIS;

typedef struct
{
    int annee[7];
    MOIS mois[12];
    float totalAnnee[7];
    float totalGen;
} TABLEAU;

int foncJour (VENTE*);
int foncMois (VENTE*);
int foncAn (VENTE*);



int main()
{
    FILE* fvente;
    FILE* edition;

    VENTE vente;
    TABLEAU tab;

    int q = 0;                          /* tableau des quinzaines: 1ere quinzaine en 0, 2e en 1 */

    int lig = 0;
    int col = 0;
    int i = 0;

    int jour = 0;                       /* variable accueillant le jour de la vente en int grâce à la fonction foncJour */
    int mois = 0;                       /* variable accueillant le mois de la vente en int grâce à la fonction foncMois */
    int an = 0;                         /* variable accueillant l'année de la vente en int grâce à la fonction foncAn */
    int crNan = 0;

    char chaineNum[150] = "";

    char LD1[150] = "";
    char LD2[150] = "";
    char LD3[150] = "";
    char LD4[150] = "";
    char LT1[150] = "";
    char ligEtoile[150]="";
    char* libMois[13] =
    {
        "*  JANVIER   *",
        "*  FEVRIER   *",
        "*  MARS      *",
        "*  AVRIL     *",
        "*  MAI       *",
        "*  JUIN      *",
        "*  JUILLET   *",
        "*  AOUT      *",
        "*  SEPTEMBRE *",
        "*  OCTOBRE   *",
        "*  NOVEMBRE  *",
        "*  DECEMBRE  *",
        "*  T O T A L *"
    };

    /*======================================================================================================================================================*/
    /*                                                               OUVERTURE DES FICHIERS                                                                 */
    /*======================================================================================================================================================*/

    fvente = fopen("R:\\C\\fichiers\\vente","rb");
    if (fvente == NULL)
    {
        printf ("*** ERREUR OUVERTURE DU FICHIER VENTE ***");
        exit(0);
    }

    edition = fopen("U:\\fichiers\\vente.txt","wt");
    if (edition == NULL)
    {
        printf ("*** ERREUR OUVERTURE DU FICHIER EDITION ***");
        exit(0);
    }

    fread (&vente,sizeof(VENTE),1,fvente);

    /*======================================================================================================================================================*/
    /*                                                           REINITIALISATION DE LA TABLE tab                                                           */
    /*======================================================================================================================================================*/

    for (lig = 0; lig <13; lig++)
    {
        for (col = 0; col < 8; col++)
        {
            tab.mois[lig].quinz1[col] = 0;
            tab.mois[lig].quinz2[col] = 0;
        }
    }



    /*======================================================================================================================================================*/
    /*                                                               REMPLISSAGE DES VALEURS                                                                */
    /*======================================================================================================================================================*/


    do
    {
        jour = foncJour (&vente);
        mois = foncMois (&vente);
        an = foncAn (&vente);

        tab.annee[an] = an;

        if (jour <=15)
        {
            tab.mois[mois].quinz1[an] += vente.prixHT;
        }
        else
        {
            tab.mois[mois].quinz2[an] += vente.prixHT;
        }

        fread (&vente,sizeof(VENTE),1,fvente);

    }
    while (!feof (fvente));


    /*======================================================================================================================================================*/
    /*                                                           FIN REMPLISSAGE DES VALEURS                                                                */
    /*======================================================================================================================================================*/

    /*======================================================================================================================================================*/
    /*                                                                CALCUL DES TOTAUX                                                                     */
    /*======================================================================================================================================================*/


    tab.totalGen = 0;

    for (lig = 0; lig < 12; lig++)
    {
        for (col = 0; col < 7; col++)
        {
            tab.mois[lig].totalMois += tab.mois[lig].quinz1[col] + tab.mois[lig].quinz2[col];            /* Calcul TOTAL MOIS */

            tab.totalAnnee[col] += tab.mois[lig].quinz1[col] + tab.mois[lig].quinz2[col];                /* Calcul TOTAL ANNEE */

        }
            tab.totalGen += tab.mois[lig].totalMois;                                                     /* Calcul TOTAL GENERAL */
    }





    /*======================================================================================================================================================*/
    /*                                                               DEBUT AFFICHAGE TABLEAU                                                                */
    /*======================================================================================================================================================*/


    /*======================================================================================================================================================*/
    /*                                                                      ENTETE                                                                          */
    /*======================================================================================================================================================*/

    placeSousChaine(LT1,"** M.GAUTHEROT Nicolas **",0,'d');
    placeSousChaine(LT1,"STATISTIQUES CHIFFRES D'AFFAIRES",50,'d');
    puts (LT1);
    printf("\n\n");
    fprintf(edition,"%s\n\n\n",LT1);

    /*======================================================================================================================================================*/
    /*                                                                    FIN ENTETE                                                                        */
    /*======================================================================================================================================================*/

    remplirChaine(ligEtoile, '*',0,133);
    puts(ligEtoile);
    fprintf(edition,"%s\n",ligEtoile);

    placeSousChaine(LD1,"*",0,'d');
    placeSousChaine(LD1,"*     2010",13,'d');
    placeSousChaine(LD1,"*     2011",28,'d');
    placeSousChaine(LD1,"*     2012",43,'d');
    placeSousChaine(LD1,"*     2013",58,'d');
    placeSousChaine(LD1,"*     2014",73,'d');
    placeSousChaine(LD1,"*     2015",88,'d');
    placeSousChaine(LD1,"*     2016",103,'d');
    placeSousChaine(LD1,"*  T O T A L   *",118,'d');
    puts(LD1);
    fprintf(edition,"%s\n",LD1);
    strcpy(LD1,"");

    puts(ligEtoile);
    fprintf(edition,"%s\n",ligEtoile);

    for (lig = 0; lig <= 12; lig++)
    {
        if (lig == 12)
        {
            for (col = 0; col <= 7; col++)
            {
                if (col == 7)
                {
                    doubleChaine(tab.totalGen, 2, chaineNum);
                    placeSousChaine(LD3, chaineNum,26 + (col * 15),'g');
                    placeSousChaine(LD3,"*",133,'d');
                }
                else
                {
                    placeSousChaine(LD2,"*",0,'d');
                    placeSousChaine(LD2,"*",13,'d');
                    placeSousChaine(LD2,"*",28 + (col * 15),'d');
                    placeSousChaine(LD2,"*",133,'d');

                    placeSousChaine(LD3, libMois[lig],0,'d');
                    doubleChaine(tab.totalAnnee[col], 2, chaineNum);
                    placeSousChaine(LD3, chaineNum,26 + (col * 15),'g');
                    placeSousChaine(LD3,"*",28 + (col * 15),'d');

                    placeSousChaine(LD4,"*",0,'d');
                    placeSousChaine(LD4,"*",13,'d');
                    placeSousChaine(LD4,"*",28 + (col * 15),'d');
                    placeSousChaine(LD4,"*",133,'d');
                }

            }
        }
        else
        {
            placeSousChaine(LD3, libMois[lig],0,'d');
            placeSousChaine(LD3,"--------------*",14,'d');
            placeSousChaine(LD3,"--------------*",29,'d');
            placeSousChaine(LD3,"--------------*",44,'d');
            placeSousChaine(LD3,"--------------*",59,'d');
            placeSousChaine(LD3,"--------------*",74,'d');
            placeSousChaine(LD3,"--------------*",89,'d');
            placeSousChaine(LD3,"--------------*",104,'d');
            doubleChaine(tab.mois[lig].totalMois,2,chaineNum);
            placeSousChaine(LD3,chaineNum,131,'g');                                /*  affichage du total des MOIS de toutes les années */
            placeSousChaine(LD3,"*",133,'d');


            for (col = 0; col < 7; col++)
            {
                placeSousChaine(LD2,"*",0,'d');
                placeSousChaine(LD2,"*",13,'d');
                doubleChaine(tab.mois[lig].quinz1[col], 2, chaineNum );
                placeSousChaine(LD2, chaineNum, 26 + (col * 15),'g');
                placeSousChaine(LD2,"*",28 + (col * 15),'d');
                placeSousChaine(LD2,"*",133,'d');


                placeSousChaine(LD4,"*",0,'d');
                placeSousChaine(LD4,"*",13,'d');
                doubleChaine(tab.mois[lig].quinz2[col], 2, chaineNum);
                placeSousChaine(LD4, chaineNum, 26 + (col * 15),'g');
                placeSousChaine(LD4,"*",28 + (col * 15),'d');
                placeSousChaine(LD4,"*",133,'d');

            }
        }

        puts(LD2);
        puts(LD3);
        puts(LD4);
        printf("\n");
        fprintf(edition,"%s\n",LD2);
        fprintf(edition,"%s\n",LD3);
        fprintf(edition,"%s\n",LD4);
        puts(ligEtoile);
        fprintf(edition,"%s\n",ligEtoile);

        strcpy(LD2,"");
        strcpy(LD3,"");
        strcpy(LD4,"");
    }



    fclose (fvente);
    fclose (edition);

    return 0;
}










/*======================================================================================================================================================*/
/*======================================================================================================================================================*/
/*                                                  FONCTIONS FONCJOUR, FONCMOIS, FONCAN                                                                */
/*======================================================================================================================================================*/
/*======================================================================================================================================================*/
int foncJour(VENTE* vente)
{
    int i = 0, j = 0, jour = 0;
    char date[11];
    char chaineJour[1];

    strcpy(date,vente->dateFac);

    for (i = 0; i<=1; i++)
    {
        chaineJour[j] = date[i];
        j++;
    }
    chaineJour[j]=0;
    jour = atoi(chaineJour);

    return jour;

}

int foncMois(VENTE* vente)
{
    int i = 0, j = 0, mois = 0;
    char date[11];
    char chaineMois[1];

    strcpy(date,vente->dateFac);

    for (i = 3; i<=4; i++)
    {
        chaineMois[j] = date[i];
        j++;
    }
    chaineMois[j]=0;
    mois = atoi(chaineMois);
    mois = mois -1;

    return mois;

}

int foncAn(VENTE* vente)
{
    int i = 0, j = 0, an = 0;
    char date[11];
    char chaineAn[3];

    strcpy(date,vente->dateFac);


    for (i = 6; i<=9; i++)
    {
        chaineAn[j] = date[i];
        j++;
    }
    chaineAn[j]=0;
    an = atoi(chaineAn);
    an = an-2010;

    return an;

}
