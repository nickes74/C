/* ========================================================================== */
/* Projet : initNotes  --  initialisation du fichier des notes des stagiaires */
/* -------------------------------------------------------------------------- */
/* Auteur :                                                                   */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "R:\C\evaluation\entetes\stagiaire.h"
#include "R:\C\evaluation\entetes\matiere.h"
#include "R:\C\evaluation\entetes\note.h"

/* ========================================================================== */
/* PROGRAMME PRINCIPAL                                                        */
/* ========================================================================== */

int main()
{
    FILE* fichierNotes;
    NOTE note;

    int numStagiaire;
    int numMatiere;

    int aDesNotes;
    int nombreNotes;
    int iNote;

    fichierNotes = fopen("U:\\fichiers\\notes", "wb");

    if (fichierNotes == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER notes ***\n");
        exit(0);
    }

    srand((unsigned)time(NULL));

    for (numStagiaire = 1; numStagiaire <= 14; numStagiaire++)
    {
        aDesNotes = rand() % 4;

        if (aDesNotes != 0)
        {
            printf("\n\n====> Stagiaire %d\n\n", numStagiaire);

            note.numStagiaire = numStagiaire;

            for (numMatiere = 1; numMatiere <= 5; numMatiere++)
            {
                nombreNotes = rand() % 4;
                printf("Matiere %d : %d\n", numMatiere, nombreNotes);

                if(nombreNotes > 0)
                {
                    note.numMatiere = numMatiere;
                    for (iNote = 1; iNote <= nombreNotes; iNote++)
                    {
                        note.note = rand() % 21;
                        printf("%d %d %d\n", note.numStagiaire, note.numMatiere, note.note);
                        fwrite(&note, sizeof(NOTE), 1, fichierNotes);
                    }
                }
            }
        }
    }

    fclose(fichierNotes);

    return 0;
}
