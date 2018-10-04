#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int numero;
    char nom[51];
    char prenom[41];
    int numeroAgence;
}EMPLOYE;

int main()
{
    FILE* fichier;

    EMPLOYE emp;

    char temp[51];
    int codeRetour;

    fichier=fopen("U:\\fichiers\\employes","wb");
    if (fichier == 0)
    {
        printf(" *** Erreur d'ouverture de fichier *** ");
        exit(0);
    }

    printf("\nEntrez le numerode l'employe : ");
    gets(temp);

    while(temp[0] != 0)
    {
        emp.numero = atoi(temp);

        printf("Nom de l'employe : ");
        gets(emp.nom);

        printf("Prenom de l'employe : ");
        gets(emp.prenom);

        printf("Numero d'agence de l'employe : ");
        gets(temp);
        emp.numeroAgence= atoi(temp);

        codeRetour = fwrite(&emp,sizeof(EMPLOYE),1,fichier);
        printf("\nCode retour : %d",codeRetour);

        printf("\nEntrez le numerode l'employe : ");
        gets(temp);

    }

    fclose(fichier);

    return 0;
}
