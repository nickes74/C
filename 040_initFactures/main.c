/* ========================================================================== */
/* Projet : initFactures                                                      */
/* -------------------------------------------------------------------------- */
/* Initialisation du fichier des factures a partir d'un fichier               */
/* texte (factures.txt)                                                       */
/* -------------------------------------------------------------------------- */
/* Dans le fichier facture.txt les trois champs (ncli, nfac, mont) sont       */
/* separes par des ';'.                                                       */
/*                                                                            */
/* Exemple : 001;01201;3000.00                                                */
/*           001;01205;1520.00                                                */
/*           001;01206;2100.00                                                */
/*           001;01211;1900.00                                                */
/*           003;01202;2500.00                                                */
/*           003;01203;900.00                                                 */
/*           003;01210;1850.00                                                */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "C:\C\utilitaires\entetes\chaines.h"

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
    FILE* fichierTexte;
    char ligne[51];

/* -------------------------------------------------------------------------- */
/* Ouverture du fichier des factures                                          */
/* -------------------------------------------------------------------------- */
    fichierFactures = fopen("C:\\c\\fichiers\\factures", "wb");

    if (fichierFactures == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER DES FACTURES ***\n");
        exit(0);
    }

/* -------------------------------------------------------------------------- */
/* Ouverture du fichier texte                                                 */
/* -------------------------------------------------------------------------- */
    fichierTexte = fopen("C:\\c\\fichiers\\factures.txt", "rt");

    if (fichierTexte == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER TEXTE ***\n");
        exit(0);
    }

/* -------------------------------------------------------------------------- */
/* Premiere lecture du fichier texte                                          */
/* -------------------------------------------------------------------------- */
    fgets(ligne, 51, fichierTexte);
    printf("%s", ligne);

/* -------------------------------------------------------------------------- */
/* Creation des enregistrements du fichier factures                           */
/* -------------------------------------------------------------------------- */
    while(!feof(fichierTexte))
    {
        isole(ligne, facture.ncli);
        isole(ligne, facture.nfac);
        facture.mont = (float) atof(ligne);

        printf("%s %s %f\n\n", facture.ncli, facture.nfac, facture.mont);

        fwrite(&facture, sizeof(FACTURE), 1, fichierFactures);

        fgets(ligne, 51, fichierTexte);
        printf("%s", ligne);
    }

    fclose(fichierFactures);
    fclose(fichierTexte);

    return 0;
}
