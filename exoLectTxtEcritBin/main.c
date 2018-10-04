#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "U:\utilitaires\entetes\chaines.h"

typedef struct
{
    int numero;
    char nom[21];
    char adresse[51];
    char codePostal[6];
    char ville[21];
    int codeSecteur;
} CONTACT;

int main()
{
    FILE* fichierTexte;
    FILE* fichierBin;
    CONTACT contact;
    char result[81];
    int n,codeRetour;
    char texte[200];
    char temp[81];


    /*===========================================================================*/
    /* Ouverture des fichiers txt à copier et dat dans lequel mettre les donnees */
    /*===========================================================================*/

    fichierTexte=fopen("U:\\fichiers\\contactsTries.txt","rt");
    if (fichierTexte == 0)
    {
        printf(" *** Erreur d'ouverture du fichier *** ");
        exit(0);
    }

    fichierBin=fopen("U:\\fichiers\\contacts.dat","wb");
    if (fichierBin == 0)
    {
        printf(" *** Erreur d'ouverture du fichier *** ");
        exit(0);
    }

    /*============================================================================*/
    /* fonction fgets permet de récupérer du texte et de le mettre dans un string */
    /*============================================================================*/

    fgets(texte,200,fichierTexte);

    while (!feof(fichierTexte))
    {
        n=0;

        while (n==0)
        {
            n=isole(texte,result);
            contact.numero=atoi(result);
            n=isole(texte,contact.nom);         /* la fonction isole (importee) permet de découper des bouts de string separes par des ";" */
            n=isole(texte,contact.adresse);
            n=isole(texte,contact.codePostal);
            n=isole(texte,contact.ville);
            n=isole(texte,result);
            contact.codeSecteur=atoi(result);

            printf ("\n%d %s %s %s %s %d",contact.numero,contact.nom,contact.adresse,contact.codePostal,contact.ville,contact.codeSecteur);

            codeRetour=fwrite(&contact,sizeof(CONTACT),1,fichierBin);
            printf("\nCode Retour : %d",codeRetour);
        }
        fgets(texte,200,fichierTexte);
    }

    fclose(fichierTexte);
    fclose(fichierBin);

    return 0;
}
