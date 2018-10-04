#include <stdio.h>
#include <stdlib.h>
#include "../../utilitaires/entetes/agences.h"      /* librairie spécifique au prototype de la fonction ayant les définitions des agences et la structure agence */

typedef struct
{
    int numero;
    char nom[51];
    char prenom[41];
    int numeroAgence;
} EMPLOYE;

int main()
{
    FILE* fichierEmploye;           /* fichier dans lequel sont les renseignements de l'employe */
    FILE* fichierAgence;            /* fichier dans lequel sont les renseignements des agences */
    EMPLOYE emp;                    /* variable de type structure ayant toutes les informations de l'employe */
    AGENCE agence;                  /* variable de type structure ayant toutes les informations de l'agence */
    int numeroEnrAgence;            /* variable dans laquelle on retourne le numero d'enregistrement des agences */

    int codeRetour;                 /* variable de test dans laquelle on met le retour du fseek sur



    /*=========================================================*/
    /* Ouverture du fichier ayant les informations des agences */
    /*=========================================================*/

    fichierAgence=fopen("U:\\fichiers\\agences","r+b");
    if (fichierAgence == 0)
    {
        printf(" *** Erreur d'ouverture de fichier *** ");
        exit(0);
    }

    /*==========================================================*/
    /* Ouverture du fichier ayant les informations des employes */
    /*==========================================================*/

    fichierEmploye=fopen("U:\\fichiers\\employes","r+b");
    if (fichierEmploye == 0)
    {
        printf(" *** Erreur d'ouverture de fichier *** ");
        exit(0);
    }

    /*=========================================================*/
    /* demarrage de la boucle de lecture des fichiers employes */
    /*=========================================================*/

    fread(&emp,sizeof(EMPLOYE),1,fichierEmploye);

    while (!feof (fichierEmploye))
    {
        numeroEnrAgence=chercheAgence(emp.numeroAgence,fichierAgence);       /* recherche du numero d'enregistrement de l'agence dans le fichier agence */

        codeRetour=fseek(fichierAgence,numeroEnrAgence*sizeof(AGENCE),SEEK_SET);    /*verification si l'agence existe vraiment grace a fseek qui pointe à l'adresse corespondante*/

        if (codeRetour != 0)
        {
            printf("\nNumero d'employe : %d",emp.numero);
            printf("\nNom : %s",emp.nom);
            printf("\nnumero agence : %d Agence Inconnue\n",emp.numeroAgence);
        }
        else
        {
            fread(&agence,sizeof(AGENCE),emp.numeroAgence,fichierAgence);   /*si l'employe a bien une agence on va chercher dans le fichier agence les données correspondantes en avançant d'autant d'adresses que le num de l'agence*/

            printf("\nNumero d'employe : %d",emp.numero);
            printf("\nNom : %s",emp.nom);
            printf("\nnumero agence : %d %s\n",emp.numeroAgence,agence.nom);
        }

        fread(&emp,sizeof(EMPLOYE),1,fichierEmploye);
    }

    fclose(fichierEmploye);
    fclose(fichierAgence);
    return 0;
}
