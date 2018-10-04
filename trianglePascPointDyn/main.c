/* ========================================================================== */
/* Projet : tablPascal2                                                       */
/* -------------------------------------------------------------------------- */
/* Triangle de Pascal : Utilisation de deux tableaux à une dimension.         */
/* ========================================================================== */

#include <stdio.h>                            /* Pour scanf, printf...        */

int main()
{
    int* ptableau1;                             /* ligne precedente             */
    int* ptableau2;                             /* ligne courante               */
    int* temp;
    int lig,col;                                /* indices de ligne,de colonne  */
    int nbl;                                    /* nombre de lignes a afficher  */

/* -------------------------------------------------------------------------- */
/* Nombre de lignes du triangle de Pascal a afficher                          */
/* -------------------------------------------------------------------------- */
    printf("Entrez le nombre de ligne(s) du tableau (max 16) : ");
    scanf("%d", &nbl);

    ptableau1=(int*) calloc (nbl,sizeof(int));
    ptableau2=(int*) calloc (nbl,sizeof(int));
    temp=(int*) calloc (nbl,sizeof(int));    /* pas indispensable d'initailiser dynamiquement le pointeur temporaire */
/* -------------------------------------------------------------------------- */
/* Initialisation de la premiere ligne du triangle : premiere colonne a 1     */
/* -------------------------------------------------------------------------- */
    ptableau1[0] = 1;
    printf("%-5d\n", ptableau1[0]);

/* -------------------------------------------------------------------------- */
/* Boucle de calcul et d'affichage des lignes suivantes                       */
/* -------------------------------------------------------------------------- */
    for (lig = 1; lig < nbl; lig++)
    {

/* -------------------------------------------------------------------------- */
/* Affichage de la premiere colonne                                           */
/* -------------------------------------------------------------------------- */
        ptableau2[0] = 1;
        printf("%-5d", ptableau2[0]);

/* -------------------------------------------------------------------------- */
/* Boucle sur les colonnes                                                    */
/* -------------------------------------------------------------------------- */
        for (col = 1; col < lig; col++)
        {
            ptableau2[col] = ptableau1[col] + ptableau1[col - 1];
            printf("%-5d", ptableau2[col]);
        }

/* -------------------------------------------------------------------------- */
/* Affichage de la diagonale                                                  */
/* -------------------------------------------------------------------------- */
        ptableau2[lig] = 1;
        printf("%-5d\n", ptableau2[lig]);

/* -------------------------------------------------------------------------- */
/* Transfert de l2 dans l1                                                    */
/* -------------------------------------------------------------------------- */
       // for (col = 1; col <= lig + 1; col++) ptableau1[col] = ptableau2[col];
       temp = ptableau1;
       ptableau1 = ptableau2 ;      /*remplacement de la ligne for précédente en donnant les addresse du tableau précédent au nouveau avant remplacement */
       ptableau2 = temp;
    }

    return 0;
}
