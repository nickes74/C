#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "U:\utilitaires\entetes\chaines.h"
#include "U:\utilitaires\entetes\client.h"

typedef struct
{
    char noComm[7];
    char noCli[5];
    char noProd[5];
    int quantite;
    char desig[21];
    float prix;
    char date[11];
} COMMANDE;

void entete (FILE*, FILE*,FILE*,FILE*,CLIENT*,COMMANDE*, int,int, char*);    /* Declaration de la fonction entete qui affiche toute l'entete à chaque nouvelle page */

int main()
{
    FILE* commande;
    FILE* commandeDep;
    FILE* factureTxt;
    FILE* fclient;

    COMMANDE comm;
    COMMANDE commdep;
    CLIENT client;

    char date[9];
    char crNcli[5]="";
    char crNclidep[5]="";
    char crNcom[5]="";
    char crNcomm[7]="";
    char crNcommd[7]="";
    char crNprod[5]="";
    char crNprodD[7]="";
    char temp[10]="";

    char lEtoile[101]="";
    char Laffiche[101]="";
    char LE1[101]="";
    char LE2[101];
    char LE3[101];
    char LE4[101];
    char LE5[101];
    char LE6[101];
    char LD1[101];
    char LT1[101];
    char LT2[101];
    char LT3[101];
    char LT4[101];

    char signe = 'C';                   /* indice "crediteur" ou debiteur (D) du client */

    int factureJour = 1;                /* numero de la facture s'incremente à chaque nouvelle facture */
    int i = 0;                          /* indice pour les boucles */
    int compteur = 0;                   /* compteur de ligne pour le saut de page */
    int page = 1;                       /* numero de page de la facture, s'incrémente sur une meme facture puis se reinitialise à 1 */

    float montant=0;
    float z01,z02,z03,z04;
    float solde = 0;                    /* calcul du solde du client */


    /*====================*/
    /* Ouverture fichiers */
    /*====================*/

    commande=fopen("U:\\fichiers\\comm","rb");
    if (commande == NULL)
    {
        printf(" **** ERREUR OUVERTURE FICHIER COMM ***");
        exit(0);
    }

    commandeDep=fopen("U:\\fichiers\\commd","rb");
    if (commandeDep == NULL)
    {
        printf(" **** ERREUR OUVERTURE FICHIER COMMD *** ");
        exit(0);
    }

    fclient=fopen("R:\\C\\fichiers\\client","rb");
    if (fclient == NULL)
    {
        printf(" **** ERREUR OUVERTURE FICHIER CLIENT *** ");
        exit(0);
    }

    factureTxt=fopen("U:\\fichiers\\facture.txt","wt");
    if (factureTxt == NULL)
    {
        printf(" **** ERREUR OUVERTURE FICHIER FACTURE.TXT ***");
        exit(0);
    }

    /*====================*/
    /* lecture des blocks */
    /*====================*/

    fread(&comm, sizeof(COMMANDE),1,commande);
    fread(&commdep, sizeof(COMMANDE),1,commandeDep);


    /*==============*/
    /* lecture date */
    /*==============*/

    _strdate(date);

    strcpy (crNcli, comm.noCli);
    strcpy (client.noCli,crNcli);

    do
    {
        /*===============================================================================================================*/
        /*                                            Debut Commande Client                                              */
        /*===============================================================================================================*/

        entete (fclient,  commande,  commandeDep, factureTxt, &client, &comm, page, factureJour, date);

        while (!feof(commande) && strcmp(crNcli,comm.noCli) == 0)
        {

            /*===============================================================================================================================*/
            /*                                             Traitement Commande                                                               */
            /*===============================================================================================================================*/

            strcpy (crNcom, comm.noComm);


            strcpy (Laffiche,"");
            placeSousChaine(Laffiche,"*",1,'d');
            placeSousChaine(Laffiche,"*",12,'d');
            placeSousChaine(Laffiche,"*",23,'d');
            placeSousChaine(Laffiche,"*",33,'d');
            placeSousChaine(Laffiche,"*",56,'d');
            placeSousChaine(Laffiche,"*",64,'d');
            placeSousChaine(Laffiche,"*",76,'d');
            placeSousChaine(Laffiche,"*",92,'d');
            printf("%s\n",Laffiche);
            fprintf(factureTxt," %s\n",Laffiche);
            compteur++;

            /*===============================================================================================================*/
            /*                                                 Ligne LD1                                                     */
            /*===============================================================================================================*/

            strcpy (LD1,"");
            placeSousChaine(LD1,"*",1,'d');
            placeSousChaine(LD1,comm.noComm,4,'d');
            placeSousChaine(LD1,"*",12,'d');
            placeSousChaine(LD1,comm.date,13,'d');
            placeSousChaine(LD1,"*",23,'d');



            while (!feof (commande) && strcmp(crNcli,comm.noCli) == 0 && strcmp (crNcom,comm.noComm) == 0)
            {
                strcpy (crNprod, comm.noProd);

                placeSousChaine(LD1,"*",1,'d');
                placeSousChaine(LD1,"*",12,'d');
                placeSousChaine(LD1,"*",23,'d');
                placeSousChaine(LD1,comm.noProd,26,'d');
                placeSousChaine(LD1,"*",33,'d');
                placeSousChaine(LD1,comm.desig,39,'d');
                placeSousChaine(LD1,"*",56,'d');

                doubleChaine(comm.quantite,0,temp);
                placeSousChaine(LD1,temp,61,'g');

                placeSousChaine(LD1,"*",64,'d');

                doubleChaine(comm.prix,2,temp);
                placeSousChaine(LD1,temp,74,'g');

                placeSousChaine(LD1,"*",76,'d');

                /*===========================================================================================================*/
                /*                                  Calcul des Montant par Ligne                                             */
                /*===========================================================================================================*/

                montant = comm.quantite * comm.prix;
                doubleChaine(montant,2,temp);
                placeSousChaine(LD1,temp,88,'g');

                z01 += montant;                                                /*   incrémentation de z01 dans Commande   */

                placeSousChaine(LD1,"*",92,'d');
                printf("%s\n",LD1);
                fprintf(factureTxt," %s\n",LD1);
                strcpy (LD1,"");
                compteur++;

                strcpy (Laffiche,"");
                placeSousChaine(Laffiche,"*",1,'d');
                placeSousChaine(Laffiche,"*",12,'d');
                placeSousChaine(Laffiche,"*",23,'d');
                placeSousChaine(Laffiche,"*",33,'d');
                placeSousChaine(Laffiche,"*",56,'d');
                placeSousChaine(Laffiche,"*",64,'d');
                placeSousChaine(Laffiche,"*",76,'d');
                placeSousChaine(Laffiche,"*",92,'d');
                compteur++;
                printf("%s \n",Laffiche);
                fprintf(factureTxt," %s \n",Laffiche);

                fread(&comm, sizeof(COMMANDE),1,commande);


/*=============================================================================================================================================*/
/*                                                  DEBUT CONDITIONNELLE RETOUR PAGE                                                           */
/*=============================================================================================================================================*/

                if (compteur >=13)
                {
                    strcpy(lEtoile,"");
                    for (i=0; i<=91; i++)
                    {
                        lEtoile[i]='*';
                    }
                    printf("\f %s\n",lEtoile);
                    fprintf(factureTxt,"\f %s\n",lEtoile);

                    strcpy (LT1,"");
                    placeSousChaine(LT1,"*",1,'d');
                    placeSousChaine(LT1,"REMISE",35,'d');

                    placeSousChaine(LT1,".....",88,'g');
                    placeSousChaine(LT1,"*",92,'d');
                    printf("%s\n",LT1);
                    fprintf(factureTxt," %s\n",LT1);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    /*===============================================================================================================*/
                    /*                                                 Ligne LT2                                                     */
                    /*===============================================================================================================*/

                    strcpy (LT2,"");
                    placeSousChaine(LT2,"*",1,'d');
                    placeSousChaine(LT2,"MONTANT HORS TVA",35,'d');

                    placeSousChaine(LT2,".....",88,'g');
                    placeSousChaine(LT2,"*",92,'d');
                    printf("%s\n",LT2);
                    fprintf(factureTxt," %s\n",LT2);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    /*===============================================================================================================*/
                    /*                                                 Ligne LT3                                                     */
                    /*===============================================================================================================*/

                    strcpy (LT3,"");
                    placeSousChaine(LT3,"*",1,'d');
                    placeSousChaine(LT3,"MONTANT TVA (19,6 %)",35,'d');

                    placeSousChaine(LT3,".....",88,'g');
                    placeSousChaine(LT3,"*",92,'d');
                    printf("%s\n",LT3);
                    fprintf(factureTxt," %s\n",LT3);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*********************",72,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);
                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",72,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    /*===============================================================================================================*/
                    /*                                                 Ligne LT4                                                     */
                    /*===============================================================================================================*/

                    strcpy (LT4,"");
                    placeSousChaine(LT4,"*",1,'d');
                    placeSousChaine(LT4,"NET A PAYER",35,'d');
                    placeSousChaine(Laffiche,"*",72,'d');

                    placeSousChaine(LT4,".....",88,'g');
                    placeSousChaine(LT4,"*",92,'d');
                    printf("%s\n",LT4);
                    fprintf(factureTxt," %s\n",LT4);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",72,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    strcpy(lEtoile,"");
                    for (i=0; i<=91; i++)
                    {
                        lEtoile[i]='*';
                    }
                    printf("  %s\n",lEtoile);
                    fprintf(factureTxt,"  %s\n",lEtoile);

                    compteur = 0;

                    printf("\n\n\f");
                    fprintf(factureTxt,"\n\n\f");

                    page++;

                    entete (fclient,  commande,  commandeDep, factureTxt, &client, &comm, page, factureJour, date);
                }



            }

/*=============================================================================================================================================*/
/*                                                FIN CONDITIONNELLE RETOUR PAGE DE COMMANDE                                                   */
/*=============================================================================================================================================*/

        }

        if (strcmp (crNcli,commdep.noCli)==0)
        {

            strcpy (Laffiche,"");
            placeSousChaine(Laffiche,"*",1,'d');
            placeSousChaine(Laffiche,"*",12,'d');
            placeSousChaine(Laffiche,"*",23,'d');
            placeSousChaine(Laffiche,"*",33,'d');
            placeSousChaine(Laffiche,"*",56,'d');
            placeSousChaine(Laffiche,"*",64,'d');
            placeSousChaine(Laffiche,"*",76,'d');
            placeSousChaine(Laffiche,"*",92,'d');
            compteur++;
            printf("%s\n",Laffiche);
            fprintf(factureTxt," %s\n",Laffiche);


            /*===============================================================================================================*/
            /*                                                 Ligne LE6                                                     */
            /*===============================================================================================================*/


            strcpy (LE6,"");
            placeSousChaine(LE6,"*",1,'d');
            placeSousChaine(LE6,"*",12,'d');
            placeSousChaine(LE6,"*",23,'d');
            placeSousChaine(LE6,"*",33,'d');
            placeSousChaine(LE6,"D E P A N N A G E",36,'d');
            placeSousChaine(LE6,"*",56,'d');
            placeSousChaine(LE6,"*",64,'d');
            placeSousChaine(LE6,"*",76,'d');
            placeSousChaine(LE6,"*",92,'d');
            compteur++;
            printf(" %s\n",LE6);
            fprintf(factureTxt," %s\n",LE6);

            strcpy (Laffiche,"");
            placeSousChaine(Laffiche,"*",1,'d');
            placeSousChaine(Laffiche,"*",12,'d');
            placeSousChaine(Laffiche,"*",23,'d');
            placeSousChaine(Laffiche,"*",33,'d');
            placeSousChaine(Laffiche,"*",56,'d');
            placeSousChaine(Laffiche,"*",64,'d');
            placeSousChaine(Laffiche,"*",76,'d');
            placeSousChaine(Laffiche,"*",92,'d');
            compteur++;
            printf("%s\n",Laffiche);
            fprintf(factureTxt," %s\n",Laffiche);

            strcpy (Laffiche,"");
            placeSousChaine(Laffiche,"*",1,'d');
            placeSousChaine(Laffiche,"*",12,'d');
            placeSousChaine(Laffiche,"*",23,'d');
            placeSousChaine(Laffiche,"*",33,'d');
            placeSousChaine(Laffiche,"*",56,'d');
            placeSousChaine(Laffiche,"*",64,'d');
            placeSousChaine(Laffiche,"*",76,'d');
            placeSousChaine(Laffiche,"*",92,'d');
            compteur++;
            printf("%s\n",Laffiche);
            fprintf(factureTxt," %s\n",Laffiche);


            strcpy (LD1,"");
            placeSousChaine(LD1,"*",1,'d');
            placeSousChaine(LD1,commdep.noComm,4,'d');
            placeSousChaine(LD1,"*",12,'d');
            placeSousChaine(LD1,commdep.date,13,'d');
            placeSousChaine(LD1,"*",23,'d');
            placeSousChaine(LD1,"*",33,'d');



            while (strcmp (commdep.noCli,crNcli)==0 && !feof (commandeDep))
            {

                placeSousChaine(LD1,"*",1,'d');
                placeSousChaine(LD1,"*",12,'d');
                placeSousChaine(LD1,"*",23,'d');
                placeSousChaine(LD1,commdep.noProd,26,'d');
                placeSousChaine(LD1,"*",33,'d');
                placeSousChaine(LD1,commdep.desig,39,'d');
                placeSousChaine(LD1,"*",56,'d');

                doubleChaine(commdep.quantite,0,temp);
                placeSousChaine(LD1,temp,61,'g');

                placeSousChaine(LD1,"*",64,'d');

                doubleChaine(commdep.prix,2,temp);
                placeSousChaine(LD1,temp,74,'g');
                placeSousChaine(LD1,"*",76,'d');

                /*=============================================================================================================*/
                /*                                  calcul des montant par ligne depannage                                     */
                /*=============================================================================================================*/

                montant = commdep.quantite * commdep.prix;
                doubleChaine(montant,2,temp);
                placeSousChaine(LD1,temp,88,'g');

                z01 += montant;

                placeSousChaine(LD1,"*",92,'d');
                compteur++;
                printf("%s \n",LD1);
                fprintf(factureTxt," %s \n",LD1);
                strcpy (LD1,"");

                strcpy (Laffiche,"");
                placeSousChaine(Laffiche,"*",1,'d');
                placeSousChaine(Laffiche,"*",12,'d');
                placeSousChaine(Laffiche,"*",23,'d');
                placeSousChaine(Laffiche,"*",33,'d');
                placeSousChaine(Laffiche,"*",56,'d');
                placeSousChaine(Laffiche,"*",64,'d');
                placeSousChaine(Laffiche,"*",76,'d');
                placeSousChaine(Laffiche,"*",92,'d');
                printf("%s\n",Laffiche);
                fprintf(factureTxt," %s\n",Laffiche);

                fread (&commdep, sizeof(COMMANDE),1,commandeDep);

/*=============================================================================================================================================*/
/*                                                  DEBUT CONDITIONNELLE RETOUR PAGE                                                             */
/*=============================================================================================================================================*/

                if (compteur >=13)
                {
                    strcpy(lEtoile,"");
                    for (i=0; i<=91; i++)
                    {
                        lEtoile[i]='*';
                    }
                    printf("\f %s\n",lEtoile);
                    fprintf(factureTxt,"\f %s\n",lEtoile);

                    strcpy (LT1,"");
                    placeSousChaine(LT1,"*",1,'d');
                    placeSousChaine(LT1,"REMISE",35,'d');

                    placeSousChaine(LT1,".....",88,'g');
                    placeSousChaine(LT1,"*",92,'d');
                    printf("%s\n",LT1);
                    fprintf(factureTxt," %s\n",LT1);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    /*===============================================================================================================*/
                    /*                                                 Ligne LT2                                                     */
                    /*===============================================================================================================*/

                    strcpy (LT2,"");
                    placeSousChaine(LT2,"*",1,'d');
                    placeSousChaine(LT2,"MONTANT HORS TVA",35,'d');

                    placeSousChaine(LT2,".....",88,'g');
                    placeSousChaine(LT2,"*",92,'d');
                    printf("%s\n",LT2);
                    fprintf(factureTxt," %s\n",LT2);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    /*===============================================================================================================*/
                    /*                                                 Ligne LT3                                                     */
                    /*===============================================================================================================*/

                    strcpy (LT3,"");
                    placeSousChaine(LT3,"*",1,'d');
                    placeSousChaine(LT3,"MONTANT TVA (19,6 %)",35,'d');

                    placeSousChaine(LT3,".....",88,'g');
                    placeSousChaine(LT3,"*",92,'d');
                    printf("%s\n",LT3);
                    fprintf(factureTxt," %s\n",LT3);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*********************",72,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);
                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",72,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    /*===============================================================================================================*/
                    /*                                                 Ligne LT4                                                     */
                    /*===============================================================================================================*/

                    strcpy (LT4,"");
                    placeSousChaine(LT4,"*",1,'d');
                    placeSousChaine(LT4,"NET A PAYER",35,'d');
                    placeSousChaine(Laffiche,"*",72,'d');

                    placeSousChaine(LT4,".....",88,'g');
                    placeSousChaine(LT4,"*",92,'d');
                    printf("%s\n",LT4);
                    fprintf(factureTxt," %s\n",LT4);

                    strcpy (Laffiche,"");
                    placeSousChaine(Laffiche,"*",1,'d');
                    placeSousChaine(Laffiche,"*",72,'d');
                    placeSousChaine(Laffiche,"*",92,'d');
                    printf("%s\n",Laffiche);
                    fprintf(factureTxt," %s\n",Laffiche);

                    strcpy(lEtoile,"");
                    for (i=0; i<=91; i++)
                    {
                        lEtoile[i]='*';
                    }
                    printf("  %s\n",lEtoile);
                    fprintf(factureTxt,"  %s\n",lEtoile);

                    compteur = 0;

                    printf("\n\n\f");
                    fprintf(factureTxt,"\n\n\f");

                    page++;

                    entete (fclient,  commande,  commandeDep, factureTxt, &client, &comm, page, factureJour, date);
                }

/*=============================================================================================================================================*/
/*                                                FIN CONDITIONNELLE RETOUR PAGE DE COMMANDE DEPANNAGE                                         */
/*=============================================================================================================================================*/

            }

            strcpy (Laffiche,"");
            placeSousChaine(Laffiche,"*",1,'d');
            placeSousChaine(Laffiche,"*",12,'d');
            placeSousChaine(Laffiche,"*",23,'d');
            placeSousChaine(Laffiche,"*",33,'d');
            placeSousChaine(Laffiche,"*",56,'d');
            placeSousChaine(Laffiche,"*",64,'d');
            placeSousChaine(Laffiche,"*",76,'d');
            placeSousChaine(Laffiche,"*",92,'d');
            printf("%s\n",Laffiche);
            fprintf(factureTxt," %s\n",Laffiche);


        }

        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",12,'d');
        placeSousChaine(Laffiche,"*",23,'d');
        placeSousChaine(Laffiche,"*",33,'d');
        placeSousChaine(Laffiche,"*",56,'d');
        placeSousChaine(Laffiche,"*",64,'d');
        placeSousChaine(Laffiche,"*",76,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);


        strcpy(lEtoile,"");
        for (i=0; i<=91; i++)
        {
            lEtoile[i]='*';
        }
        printf("  %s\n",lEtoile);
        fprintf(factureTxt,"  %s\n",lEtoile);

        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);
        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);

        /*===============================================================================================================*/
        /*                                           Debut affichage totaux                                              */
        /*===============================================================================================================*/


        /*===============================================================================================================*/
        /*                                                 Ligne LT1                                                     */
        /*===============================================================================================================*/

        strcpy (LT1,"");
        placeSousChaine(LT1,"*",1,'d');
        placeSousChaine(LT1,"REMISE",35,'d');

        montant = z01 * 0.02;                                                  /* Calcul Remise */
        doubleChaine(montant,2,temp);

        placeSousChaine(LT1,temp,88,'g');
        placeSousChaine(LT1,"*",92,'d');
        printf("%s\n",LT1);
        fprintf(factureTxt," %s\n",LT1);

        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);

        /*===============================================================================================================*/
        /*                                                 Ligne LT2                                                     */
        /*===============================================================================================================*/

        strcpy (LT2,"");
        placeSousChaine(LT2,"*",1,'d');
        placeSousChaine(LT2,"MONTANT HORS TVA",35,'d');

        z02 = z01 - montant;                                      /* Calcul Montant Hors Taxe après remise Remise */
        doubleChaine(z02,2,temp);

        placeSousChaine(LT2,temp,88,'g');
        placeSousChaine(LT2,"*",92,'d');
        printf("%s\n",LT2);
        fprintf(factureTxt," %s\n",LT2);

        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);

        /*===============================================================================================================*/
        /*                                                 Ligne LT3                                                     */
        /*===============================================================================================================*/

        strcpy (LT3,"");
        placeSousChaine(LT3,"*",1,'d');
        placeSousChaine(LT3,"MONTANT TVA (19,6 %)",35,'d');

        z03 = z02 * 0.196;                                                    /* Calcul de la TVA */
        doubleChaine(z03,2,temp);

        placeSousChaine(LT3,temp,88,'g');
        placeSousChaine(LT3,"*",92,'d');
        printf("%s\n",LT3);
        fprintf(factureTxt," %s\n",LT3);

        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);

        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*********************",72,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);
        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",72,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);

        /*===============================================================================================================*/
        /*                                                 Ligne LT4                                                     */
        /*===============================================================================================================*/

        strcpy (LT4,"");
        placeSousChaine(LT4,"*",1,'d');
        placeSousChaine(LT4,"NET A PAYER",35,'d');
        placeSousChaine(Laffiche,"*",72,'d');

        z04 = z02 + z03;
        doubleChaine(z04,2,temp);

        placeSousChaine(LT4,temp,88,'g');
        placeSousChaine(LT4,"*",92,'d');
        printf("%s\n",LT4);
        fprintf(factureTxt," %s\n",LT4);

        strcpy (Laffiche,"");
        placeSousChaine(Laffiche,"*",1,'d');
        placeSousChaine(Laffiche,"*",72,'d');
        placeSousChaine(Laffiche,"*",92,'d');
        printf("%s\n",Laffiche);
        fprintf(factureTxt," %s\n",Laffiche);

        strcpy(lEtoile,"");
        for (i=0; i<=91; i++)
        {
            lEtoile[i]='*';
        }
        printf("  %s\n",lEtoile);
        fprintf(factureTxt,"  %s\n",lEtoile);

        printf("Ancien solde client: %c %.2f",client.codSit,client.solde);
        fprintf(factureTxt,"Ancien solde client: %c %.2f",client.codSit,client.solde);

        if (client.codSit == 'C')
        {
            solde = client.solde - z04;


            if (solde < 0)
            {
                solde = solde* -1;
                signe = 'D';
            }
        }
        else
        {
            solde= client.solde + z04;
            signe = 'D';
        }
        printf("\nNouveau solde client: %c %.2f",signe,solde);
        fprintf(factureTxt,"\nNouveau solde client: %c %.2f",signe,solde);


        printf("\n\n\n\n");
        fprintf(factureTxt,"\n\n\n\n");

        strcpy (crNcli, comm.noCli);
        strcpy (client.noCli,crNcli);

        z01 = 0;
        z02 = 0;
        z03 = 0;
        z04 = 0;
        solde = 0;
        signe = 'C';

        factureJour++;                                              /* Incrementation de la Facture */
        compteur = 0;
        page = 1;
    }
    while (!feof(commande));


    fclose(commande);
    fclose(commandeDep);
    fclose(factureTxt);
    fclose(fclient);

    return 0;
}

/*================================================================================================================================================*/
/*================================================================================================================================================*/
/*                                                          FONCTION ENTETE                                                                       */
/*================================================================================================================================================*/
/*================================================================================================================================================*/



void entete (FILE* fclient, FILE* commande, FILE* commandeDep, FILE* factureTxt,CLIENT* client,COMMANDE* comm,int page, int factureJour, char* date)
{

    char lEtoile[101]="";
    char Laffiche[101]="";
    char LE1[101]="";
    char LE2[101]="";
    char LE3[101]="";
    char LE4[101]="";
    char LE5[101]="";
    char temp[10]="";

    int i=0;

    litClient(client,fclient);

    /*==============*/
    /* lecture date */
    /*==============*/

    _strdate(date);

    /*===============================================================================================================*/
    /*                                               Affichage ENTETE                                                */
    /*===============================================================================================================*/

    strcpy(lEtoile,"");
    for (i=0; i<=91; i++)
    {
        lEtoile[i]='*';
    }
    printf("\f %s\n",lEtoile);
    fprintf(factureTxt,"\f %s\n",lEtoile);

    /*===============================================================================================================*/
    /*                                                 Ligne LE1                                                     */
    /*===============================================================================================================*/

    strcpy (LE1,"");
    placeSousChaine(LE1,"*",1,'d');
    placeSousChaine(LE1,"CLIENT NO :",4,'d');
    placeSousChaine(LE1,comm->noCli,19,'g');
    placeSousChaine(LE1,"PAGE :",25,'d');

    doubleChaine(page,0,temp);

    placeSousChaine(LE1,temp,34,'g');
    placeSousChaine(LE1,"*",46,'d');
    placeSousChaine(LE1,"*",92,'g');
    printf("%s\n",LE1);
    fprintf(factureTxt," %s\n",LE1);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",46,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",46,'d');
    placeSousChaine(Laffiche,"BIO S.A",49,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",46,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",46,'d');
    placeSousChaine(Laffiche,"20 rue PIERRE CURIE   75011 PARIS",49,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",46,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    /*===============================================================================================================*/
    /*                                                 Ligne LE2                                                     */
    /*===============================================================================================================*/

    strcpy (LE2,"");
    placeSousChaine(LE2,"*",1,'d');
    litClient(client,fclient);
    placeSousChaine(LE2,client->nom,9,'d');
    placeSousChaine(LE2,"*",46,'d');
    placeSousChaine(LE2,"*",92,'d');
    printf("%s\n",LE2);
    fprintf(factureTxt," %s\n",LE2);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",46,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    /*===============================================================================================================*/
    /*                                                 Ligne LE3                                                     */
    /*===============================================================================================================*/

    strcpy (LE3,"");
    placeSousChaine(LE3,"*",1,'d');
    placeSousChaine(LE3,client->adresse,9,'d');
    placeSousChaine(LE3,"*",46,'d');
    placeSousChaine(LE3,"CAPITAL : 2.500.000 €",49,'d');
    placeSousChaine(LE3,"*",92,'d');
    printf("%s\n",LE3);
    fprintf(factureTxt," %s\n",LE3);

    /*===============================================================================================================*/
    /*                                                 Ligne LE4                                                     */
    /*===============================================================================================================*/

    strcpy (LE4,"");
    placeSousChaine(LE4,"*",1,'d');
    placeSousChaine(LE4,client->cPost,9,'d');
    placeSousChaine(LE4,client->ville,15,'d');
    placeSousChaine(LE4,"*",46,'d');
    placeSousChaine(LE4,"RC PARIS 38 B 901",49,'d');
    placeSousChaine(LE4,"*",92,'d');
    printf("%s\n",LE4);
    fprintf(factureTxt," %s\n",LE4);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",46,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"***********************************************",46,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    /*===============================================================================================================*/
    /*                                                 Ligne LE5                                                     */
    /*===============================================================================================================*/

    strcpy (LE5,"");
    placeSousChaine(LE5,"*",1,'d');
    placeSousChaine(LE5,"FACTURE NO:",9,'d');

    //doubleChaine(factureJour,0,tempfac);                       /* Changement de type du numero de facture */

    placeSousChaine(LE5,"001",21,'d');
    placeSousChaine(LE5,"DU",30,'d');
    placeSousChaine(LE5,date,35,'d');
    placeSousChaine(LE5,client->codPays,79,'d');
    placeSousChaine(LE5,client->noRep,83,'d');
    placeSousChaine(LE5,"*",92,'d');
    printf("%s\n",LE5);
    fprintf(factureTxt," %s\n",LE5);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"*",1,'d');
    placeSousChaine(Laffiche,"*",92,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    for (i=0; i<=91; i++)
    {
        lEtoile[i]='*';
    }
    printf("  %s\n",lEtoile);
    fprintf(factureTxt,"  %s\n",lEtoile);

    strcpy (Laffiche,"");
    placeSousChaine(Laffiche,"* COMMANDE *",1,'d');
    placeSousChaine(Laffiche,"DATE",16,'d');
    placeSousChaine(Laffiche,"* PRODUIT *",23,'d');
    placeSousChaine(Laffiche,"DESIGNATION",39,'d');
    placeSousChaine(Laffiche,"* QUANT *",56,'d');
    placeSousChaine(Laffiche,"PRIX HT  *",67,'d');
    placeSousChaine(Laffiche,"MONTANT HT   *",79,'d');
    printf("%s\n",Laffiche);
    fprintf(factureTxt," %s\n",Laffiche);

    strcpy(lEtoile,"");
    for (i=0; i<=91; i++)
    {
        lEtoile[i]='*';
    }
    printf("  %s\n",lEtoile);
    fprintf(factureTxt,"  %s\n",lEtoile);


    /*====================================================================================================================================*/
    /*                                                   FIN DECO ENTETE                                                                  */
    /*====================================================================================================================================*/
}
