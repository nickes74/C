/* ========================================================================== */
/* Premiere version : test (technique) de lecture du fichier des factures     */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

/* -------------------------------------------------------------------------- */
/* Ouverture du fichier des factures                                          */
/* -------------------------------------------------------------------------- */
    fichierFactures = fopen("R:\\c\\fichiers\\factures", "rb");

    if (fichierFactures == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER DES FACTURES ***\n");
        exit(0);
    }

/* -------------------------------------------------------------------------- */
/* Test de lecture du fichier facture                                         */
/* -------------------------------------------------------------------------- */
    fread(&facture, sizeof(FACTURE), 1, fichierFactures);

    printf("%s  %s  %9.2f\n\n", facture.ncli,
           facture.nfac,
           facture.mont);

/* -------------------------------------------------------------------------- */
/* Fermeture du fichier des factures                                          */
/* -------------------------------------------------------------------------- */
    fclose(fichierFactures);

    return 0;
}
