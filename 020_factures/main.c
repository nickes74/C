/* ========================================================================== */
/* Deuxieme version : tests des structures logiques                           */
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

    char crNcli[4];

/* Ouverture du fichier des factures  */

    fichierFactures = fopen("C:\\c\\fichiers\\factures", "rb");

    if (fichierFactures == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER DES FACTURES ***\n");
        exit(0);
    }

/* Debut programme */

    fread(&facture, sizeof(FACTURE), 1, fichierFactures);

    do
    {

/* Debut client */

        strcpy(crNcli, facture.ncli);
        printf("CLIENT : %s\n", crNcli);

        do
        {

/* Debut facture */

            printf("       %s   %7.2f", facture.nfac, facture.mont);

            if (facture.mont > 2000.00)
            {

/* Traitement remise */

                printf("    >  2000.00\n");
            }
            else
            {

/* Traitement pas remise */

                printf("    <= 2000.00\n");
            }

/* Fin facture */

            fread(&facture, sizeof(FACTURE), 1, fichierFactures);
        }
        while ((strcmp(facture.ncli, crNcli) == 0) && (!feof(fichierFactures)));

/* Fin client */

    }
    while (!feof(fichierFactures));

/* Fin programme */

    fclose(fichierFactures);

    return 0;
}

