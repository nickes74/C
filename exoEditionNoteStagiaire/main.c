#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "R:\C\evaluation\entetes\stagiaire.h"
#include "R:\C\evaluation\entetes\matiere.h"
#include "R:\C\evaluation\entetes\note.h"
#include "U:\utilitaires\entetes\chaines.h"


int main()
{
    FILE* fnote;
    FILE* fmatiere;
    FILE* fstagiaire;
    FILE* fedition;

    NOTE note;
    MATIERE matiere;
    STAGIAIRE stagiaire;

    int crNmat = 0;                /* CRITERE DE COMPARAISON DES MATIERES */

    float somme = 0;               /* SOMME DES NOTES PAR MATIERE */
    float div = 0;                 /* DIVISEUR POUR LA MOYENNE */
    float moy = 0;                 /* MOYENNE DES NOTES */


/*==============================================================*/
/*                      OUVERTURE DES FICHIERS                  */
/*==============================================================*/

    fnote = fopen("U:\\fichiers\\notes","rb");
    if (fnote == NULL)
    {
        printf("*** ERREUR OUVERTURE NOTE ***");
        exit(0);
    }

    fmatiere = fopen("R:\\C\\evaluation\\fichiers\\matieres","rb");
    if (fmatiere == NULL)
    {
        printf("*** ERREUR OUVERTURE MATIERE ***");
        exit(0);
    }

    fstagiaire = fopen("R:\\C\\evaluation\\fichiers\\stagiaires","rb");
    if (fstagiaire == NULL)
    {
        printf("*** ERREUR OUVERTURE STAGIAIRES ***");
        exit(0);
    }

    fedition = fopen ("U:\\fichiers\\noteStagiaires.txt","wt");
    if (fedition == NULL)
    {
        printf("*** ERREUR OUVERTURE EDITION ***");
        exit(0);
    }


    fread (&note,sizeof(NOTE),1,fnote);

    fread (&stagiaire,sizeof(STAGIAIRE),1,fstagiaire);


/*==============================================================*/
/*                        DEBUT PROGRAMME                       */
/*==============================================================*/

    while (!feof (fstagiaire))
    {

/*==============================================================*/
/*                  OUVERTURE FICHIER STAGIAIRE                 */
/*==============================================================*/


        fprintf(fedition,"Stagiaire :%3d  %10s %10s\n\n",stagiaire.numero,
                                                    stagiaire.nom,
                                                    stagiaire.prenom);





        if (note.numStagiaire == stagiaire.numero)   /* TEST SI LE STAGIAIRE A UNE NOTE */
        {
            while (note.numStagiaire == stagiaire.numero && !feof(fnote))
            {
                crNmat = note.numMatiere;
                somme = 0;
                div = 0;
                moy = 0;

                while (note.numMatiere == crNmat && !feof(fnote))  /* TT NOTES PAR MATIERE */
                {
                    somme += note.note;
                    div++;

                    fread (&note,sizeof(NOTE),1,fnote); /* LECTURE NOTE SUIVANTE */
                }

                moy = somme / div;

                matiere.numMatiere = crNmat;
                litMatiere(&matiere,fmatiere);     /* RECHERCHE NOM DE LA MATIERE */

                fprintf(fedition,"%s moyenne : %5.2f\n",matiere.nomMatiere, moy);

                fread (&note,sizeof(NOTE),1,fnote);  /* LECTURE NOTE SUIVANTE */
            }

        }
        else                                        /* ECRITURE SI PAS DE NOTE */
        {
            fprintf (fedition,"Ce stagiaire n'a pas de note.\n\n");
        }

        fprintf(fedition,"\n\n");

        fread (&stagiaire,sizeof(STAGIAIRE),1,fstagiaire);    /* STAGIAIRE SUIVANT */

    }                                               /* FIN BOUCLE SUR STAGIAIRE */

/*==============================================================*/
/*           FIN PROGRAMME - FERMETURE DES FICHIERS             */
/*==============================================================*/

    fclose(fnote);
    fclose(fmatiere);
    fclose(fstagiaire);
    fclose(fedition);

    return 0;
}
