#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "U:\utilitaires\entetes\chaines.h"

typedef struct
{
    char NoComm[7];
    char noCli[5];
    char noProd[5];
    int quantite;
    char desig[21];
    float prix;
    char date[11];
} COMMANDE;

typedef struct
{
    char noCli[5];
    char dateFac[11];
    char noProd[5];
    int quantite;
    float prixHT;
} VENTE;


int main()
{
    FILE* fcomm;
    FILE* fcommDep;
    FILE* fvente;
    FILE* fvente1;

    COMMANDE comm;
    COMMANDE commd;
    VENTE vente;
    VENTE vente1;


//    char* dat = "01/01/2015";
    char dat[11] = "";

    char crNcli[5] = "";

    int compteur = 0;


    /*===========================================================================================================================================================*/
    /*                                                              OUVERTURE DES FICHIERS                                                                       */
    /*===========================================================================================================================================================*/

    fcomm = fopen ("R:\\C\\fichiers\\comm","rb");
    if (fcomm == NULL)
    {
        printf ("*** ERREUR OUVERTURE FICHIER COMM");
        exit (0);
    }

    fcommDep = fopen ("R:\\C\\fichiers\\commd","rb");
    if (fcommDep == NULL)
    {
        printf ("*** ERREUR OUVERTURE FICHIER COMMD");
        exit (0);
    }

    fvente = fopen ("R:\\C\\fichiers\\vente","rb");
    if (fvente == NULL)
    {
        printf ("*** ERREUR OUVERTURE FICHIER VENTE");
        exit (0);
    }

    fvente1 = fopen ("U:\\fichiers\\vente1","wb");
    if (fvente1 == NULL)
    {
        printf ("*** ERREUR OUVERTURE FICHIER VENTE1");
        exit (0);
    }



    /*===========================================================================================================================================================*/
    /*                                                              LECTURE DES STRUCTURES                                                                       */
    /*===========================================================================================================================================================*/

    fread (&comm, sizeof(COMMANDE),1,fcomm);
    if (feof (fcomm)) chaineMax (comm.noCli, sizeof(comm.noCli));

    fread (&commd, sizeof(COMMANDE),1,fcommDep);
    if (feof (fcommDep)) chaineMax (commd.noCli, sizeof(commd.noCli));


    fread (&vente, sizeof(VENTE),1,fvente);
    if (feof (fvente)) chaineMax (vente.noCli, sizeof(vente.noCli));


    printf ("Entrez l'annee de facturation : ");
    gets(dat);


    do
    {

        /*===========================================================================================================================================================*/
        /*                                                             DEBUT COMPARAISON NOCLI                                                                       */
        /*===========================================================================================================================================================*/

        if (strcmp (vente.noCli, comm.noCli) > 0)
        {
            strcpy (crNcli, comm.noCli);
        }
        else
        {
            strcpy (crNcli,vente.noCli);
        }

        if (strcmp (crNcli, commd.noCli) > 0)
        {
            strcpy (crNcli, commd.noCli);
        }

        /*===========================================================================================================================================================*/
        /*                                                        DEBUT RENSEIGNEMENT SELON NOCLI                                                                    */
        /*===========================================================================================================================================================*/

        if (strcmp (crNcli,vente.noCli) == 0)                       /* Remplissage vente1 si client = client de vente */
        {
            do
            {
//                strcpy(vente1.noCli, vente.noCli);
//                strcpy(vente1.dateFac, vente.dateFac);
//                strcpy(vente1.noProd, vente.noProd);
//                vente1.quantite = vente.quantite;
//                vente1.prixHT = vente.prixHT;

                vente1 = vente;


                fwrite(&vente1,sizeof(VENTE),1,fvente1);
                compteur++;

                printf("noCli : %5s date : %11s noProd : %4s quantite : %4d prix : %7.2f\n",vente1.noCli,
                       vente1.dateFac,
                       vente1.noProd,
                       vente1.quantite,
                       vente1.prixHT);

                fread (&vente,sizeof(VENTE),1,fvente);
                if (feof (fvente)) chaineMax (vente.noCli, sizeof(vente.noCli));

            }
            while (strcmp (crNcli,vente.noCli) == 0);

        }
        else if (strcmp (crNcli,comm.noCli) == 0)
        {
            do
            {
                strcpy(vente1.noCli, comm.noCli);
                strcpy(vente1.dateFac, dat);
                strcpy(vente1.noProd, comm.noProd);
                vente1.quantite = comm.quantite;
                vente1.prixHT = comm.quantite * comm.prix;

                fwrite(&vente1,sizeof(VENTE),1,fvente1);
                compteur++;

                printf("noCli : %5s date : %11s noProd : %4s quantite : %4d prix : %7.2f\n",vente1.noCli,
                       vente1.dateFac,
                       vente1.noProd,
                       vente1.quantite,
                       vente1.prixHT);

                fread (&comm, sizeof(COMMANDE),1,fcomm);
                if (feof (fcomm)) chaineMax (comm.noCli, sizeof(comm.noCli));


            }
            while (strcmp (crNcli,comm.noCli) == 0);
        }
        else if (strcmp (crNcli,commd.noCli) == 0)
        {
            do
            {
                strcpy(vente1.noCli, commd.noCli);
                strcpy(vente1.dateFac, dat);
                strcpy(vente1.noProd, commd.noProd);
                vente1.quantite = commd.quantite;
                vente1.prixHT = commd.quantite * commd.prix;

                fwrite(&vente1,sizeof(VENTE),1,fvente1);
                compteur++;

                printf("noCli : %5s date : %11s noProd : %4s quantite : %4d prix : %7.2f\n",vente1.noCli,
                       vente1.dateFac,
                       vente1.noProd,
                       vente1.quantite,
                       vente1.prixHT);

                fread (&commd, sizeof(COMMANDE),1,fcommDep);
                if (feof (fcommDep)) chaineMax (commd.noCli, sizeof(commd.noCli));


            }
            while (strcmp (crNcli,commd.noCli) == 0);
        }

        printf("\n");

    }
    while (!feof(fvente) || !feof(fcomm) || !feof(fcommDep));

    printf("\nnombre de lignes : %d", compteur);

    fclose(fcomm);
    fclose(fcommDep);
    fclose(fvente);
    fclose(fvente1);

    return 0;
}
