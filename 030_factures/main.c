/* ========================================================================== */
/* Factures -- Programme complet                                              */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "C:\c\utilitaires\entetes\chaines.h"


typedef struct
{
    char  ncli[4];
    char  nfac[6];
    float mont;
} FACTURE;


int main()
{
    FACTURE facture;
    FILE* fichierFactures;
    FILE* edition;
    char crNcli[4];
    float remise;

    char ligneEdition1[81] = "";
    char ligneEdition2[81] = "";

    char chaineNum[81];

/* -------------------------------------------------------------------------- */
/* Ouverture du fichier des factures                                          */
/* -------------------------------------------------------------------------- */
    fichierFactures = fopen("C:\\c\\fichiers\\factures", "rb");

    if (fichierFactures == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER DES FACTURES ***\n");
        exit(0);
    }

/* -------------------------------------------------------------------------- */
/* Ouverture du fichier d'edition                                             */
/* -------------------------------------------------------------------------- */
    edition = fopen("C:\\c\\fichiers\\editFactures.txt", "wt");

    if (edition == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER EDITION ***\n");
        exit(0);
    }

/* -------------------------------------------------------------------------- */
/* Debut programme : lecture initiale                                         */
/* -------------------------------------------------------------------------- */
    fread(&facture, sizeof(FACTURE), 1, fichierFactures);

    do
    {

/* -------------------------------------------------------------------------- */
/* Debut client                                                               */
/* -------------------------------------------------------------------------- */
        strcpy(crNcli, facture.ncli);

        placeSousChaine(ligneEdition1, "CLIENT :", 0, 'd');
        placeSousChaine(ligneEdition1, facture.ncli, 9, 'd');
        fprintf(edition, "%s\n\n", ligneEdition1);
        strcpy(ligneEdition1, "");

        do
        {

/* -------------------------------------------------------------------------- */
/* Debut facture                                                              */
/* -------------------------------------------------------------------------- */
            placeSousChaine(ligneEdition2, facture.nfac, 9, 'd');
            doubleChaine(facture.mont, 2, chaineNum);
            placeSousChaine(ligneEdition2, chaineNum, 26, 'g');

            if (facture.mont > 2000.00)
            {

/* -------------------------------------------------------------------------- */
/* Traitement remise                                                          */
/* -------------------------------------------------------------------------- */
                remise = facture.mont * 0.1f;
                doubleChaine(remise, 2, chaineNum);
                placeSousChaine(ligneEdition2, chaineNum, 35, 'g');
            }

/* -------------------------------------------------------------------------- */
/* Fin facture                                                                */
/* -------------------------------------------------------------------------- */
            fprintf(edition, "%s\n", ligneEdition2);
            strcpy(ligneEdition2, "");
            fread(&facture, sizeof(FACTURE), 1, fichierFactures);
        }
        while ((strcmp(facture.ncli, crNcli) == 0) && (!feof(fichierFactures)));

/* -------------------------------------------------------------------------- */
/* Fin client                                                                 */
/* -------------------------------------------------------------------------- */
        fprintf(edition, "\n\n");
    }
    while (!feof(fichierFactures));

/* -------------------------------------------------------------------------- */
/* Fin programme                                                              */
/* -------------------------------------------------------------------------- */
    fclose(fichierFactures);
    fclose(edition);

    return 0;
}
