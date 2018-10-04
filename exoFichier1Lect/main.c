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

    fichier=fopen("U:\\fichiers\\employes","rb");
    if (fichier == 0)
    {
        printf(" *** Erreur d'ouverture de fichier *** ");
        exit(0);
    }

    printf("Liste des Employes : \n\n");

    fread(&emp,sizeof(EMPLOYE),1,fichier);

    while (!feof (fichier))
    {
        printf("%3d %s %s %d\n",emp.numero,emp.nom,emp.prenom,emp.numeroAgence);
        fread(&emp,sizeof(EMPLOYE),1,fichier);
    }

    fclose(fichier);

    return 0;
}
