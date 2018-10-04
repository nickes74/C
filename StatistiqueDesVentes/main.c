#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "U:\utilitaires\entetes\chaines.h"
#include "U:\utilitaires\entetes\dateEu.h"

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
    FILE* fichierVersement;
    FILE* fichierVersTraite;

    char dat[9];
    char date[9];
    char crNsect[3];
    char crNrep[4];
    char crNcli[5];
    char LE1[81]="";
    char LE2[81]="";
    char LE3[81]="";
    char LD1[81]="";
    char LT1[81]="";
    char LT2[81]="";
    char LT3[81]="";
    char chaineZ01[81]="";

    double z01=0;
    double z02=0;
    double z03=0;
    double z04=0;
    double z05=0;
    double z06=0;
    double z07=0;
    double z08=0;
    double z09=0;
    double z10=0;
    double z11=0;



    fichierVersement = fopen("R:\\C\\fichiers\\versements","rb");

    if (fichierVersement == NULL)
    {
        printf(" *** ERREUR OUVERTURE FICHIER DES VERSEMENTS *** ");
        exit(0);
    }

    fichierVersTraite = fopen("U:\\fichiers\\versements.txt","wt");

    if (fichierVersTraite == NULL)
    {
        printf(" *** ERREUR OUVERTURE/ECRITURE FICHIER DES VERSEMENTS *** ");
        exit(0);
    }

    /*====================================*/
    /* debut programme : lecture initiale */
    /*====================================*/

    fread (&versement, sizeof(VERSEMENT),1,fichierVersement);

    _strdate(dat);
    strcpy(date,dateEu(dat));

    do
    {
        /*===============*/
        /* Debut Secteur */
        /*===============*/

        placeSousChaine(LE1,date,1,'d');
        placeSousChaine(LE1,"STATISTIQUE MENSUELLE DES VENTES",17,'d');
        fprintf(fichierVersTraite,"\f%s\n\n",LE1);
        printf("\f%s\n\n",LE1);

        placeSousChaine(LE2,"SECTEUR",29,'d');
        placeSousChaine(LE2,versement.nosect,37,'d');
        fprintf(fichierVersTraite,"%s\n\n",LE2);
        printf("\n%s\n\n",LE2);

        placeSousChaine(LE3,"REPRESENTANT",1,'d');
        placeSousChaine(LE3,"CLIENT",15,'d');
        placeSousChaine(LE3,"MONTANT FRANCE",24,'d');
        placeSousChaine(LE3,"MONTANT EXPORT",41,'d');
        placeSousChaine(LE3,"PRIME",59,'d');
        fprintf(fichierVersTraite,"%s\n\n",LE3);
        printf("\n%s\n\n",LE3);


        strcpy (crNsect,versement.nosect);

        z06 = 0;
        z07 = 0;
        z08 = 0;

        do
        {
            /*====================*/
            /* Debut Representant */
            /*====================*/


            strcpy (crNrep,versement.norep);

            placeSousChaine(LD1,versement.norep,5,'d');

            z03 = 0;
            z04 = 0;

            do
            {
                /*==============*/
                /* Debut Client */
                /*==============*/

                strcpy (crNcli,versement.nocli);

                z01 = 0;
                z02 = 0;

                do
                {
                    /*===============================*/
                    /* Calcul des Facture par client */
                    /*===============================*/

                    placeSousChaine(LD1,versement.nocli,16,'d');

                    if (strlen(versement.codpays) == 0)         /* reperage d'un code pays ou pas */
                    {
                        z01 += versement.mont;                  /* somme montant france par client */
                    }
                    else
                    {
                        z02 += versement.mont;                  /* somme montant export par client */
                    }

                    fread (&versement, sizeof(VERSEMENT),1,fichierVersement);
                }
                while ((strcmp(versement.nocli,crNcli) == 0) && (strcmp(versement.norep,crNrep) == 0) && (strcmp(versement.nosect,crNsect) == 0) && (!feof(fichierVersement)));

                /*=========================================================*/
                /* transformation en chaine de char et affichage ligne LD1 */
                /*=========================================================*/

                doubleChaine(z01,2,chaineZ01);
                placeSousChaine(LD1,chaineZ01,35,'g');

                doubleChaine(z02,2,chaineZ01);
                placeSousChaine(LD1,chaineZ01,52,'g');

                printf("%s",LD1);
                fprintf(fichierVersTraite,"%s\n",LD1);

                //printf("\n%f\n",z01);     /* essai somme france */

                printf("\n");

                strcpy(LD1,"");

                z03 = z03+z01;                /* somme montant france par representant */
                z04 = z04+z02;                /* somme montant export par representant */

            }
            while ((strcmp(versement.norep,crNrep) == 0) && (strcmp(versement.nosect,crNsect) == 0) && (!feof(fichierVersement)));

            z05=(z03+z04)*0.015;            /* clacul prime par representant */

            z06 += z03;                     /* somme montant france par secteur */
            z07 += z04;                     /* somme montant export par secteur */
            z08 += z05;                     /* somme prime representant par secteur */

            /*=========================================================*/
            /* transformation en chaine de char et affichage ligne LT1 */
            /*=========================================================*/

            placeSousChaine(LT1,"TOTAL REPRESENTANT",1,'d');

            doubleChaine(z03,2,chaineZ01);
            placeSousChaine(LT1,chaineZ01,35,'g');

            doubleChaine(z04,2,chaineZ01);
            placeSousChaine(LT1,chaineZ01,52,'g');

            doubleChaine(z05,2,chaineZ01);
            placeSousChaine(LT1,chaineZ01,65,'g');

            printf("\n%s\n\n",LT1);
            fprintf(fichierVersTraite,"\n%s\n\n",LT1);

            strcpy(LT1,"");


        }
        while ((strcmp(versement.nosect,crNsect) == 0) && (!feof(fichierVersement)));

        z09 += z06;                         /* somme montant france totale */
        z10 += z07;                         /* somme montant export totale */
        z11 += z08;                         /* somme prime totale */

        /*=========================================================*/
        /* transformation en chaine de char et affichage ligne LT2 */
        /*=========================================================*/

        placeSousChaine(LT2,"TOTAL SECTEUR",1,'d');

        doubleChaine(z06,2,chaineZ01);
        placeSousChaine(LT2,chaineZ01,35,'g');

        doubleChaine(z07,2,chaineZ01);
        placeSousChaine(LT2,chaineZ01,52,'g');

        doubleChaine(z08,2,chaineZ01);
        placeSousChaine(LT2,chaineZ01,65,'g');

        printf("\n%s\n\n",LT2);
        fprintf(fichierVersTraite,"\n%s\n\n",LT2);

        printf("\n");

        strcpy(LT2,"");

    }
    while (!feof (fichierVersement));

    /*=========================================================*/
    /* transformation en chaine de char et affichage ligne LT3 */
    /*=========================================================*/

    placeSousChaine(LT3,"TOTAL GENERAL",1,'d');

    doubleChaine(z09,2,chaineZ01);
    placeSousChaine(LT3,chaineZ01,35,'g');

    doubleChaine(z10,2,chaineZ01);
    placeSousChaine(LT3,chaineZ01,52,'g');

    doubleChaine(z11,2,chaineZ01);
    placeSousChaine(LT3,chaineZ01,65,'g');

    printf("\n%s\n\n",LT3);
    fprintf(fichierVersTraite,"\n%s\n\n",LT3);

    fclose(fichierVersement);
    fclose(fichierVersTraite);

    return 0;
}
