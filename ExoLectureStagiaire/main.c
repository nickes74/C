/* ========================================================================== */
/* Projet : lireFichiers  --  Lecture des fichiers de l'evaluation Stagiaires */
/* -------------------------------------------------------------------------- */
/* Auteur : Michel Gineste                                                    */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "R:\C\evaluation\entetes\stagiaire.h"
#include "R:\C\evaluation\entetes\matiere.h"
#include "R:\C\evaluation\entetes\note.h"

/* ========================================================================== */
/* PROGRAMME PRINCIPAL                                                        */
/* ========================================================================== */

int main()
{
    FILE* fichierStagiaires;
    FILE* fichierMatieres;
    FILE* fichierNotes;
    FILE* edition;

    STAGIAIRE stagiaire;
    MATIERE matiere;
    NOTE note;

    fichierStagiaires = fopen("R:\\C\\evaluation\\fichiers\\stagiaires", "rb");

    if (fichierStagiaires == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER stagiaires ***\n");
        exit(0);
    }

    fichierMatieres = fopen("R:\\C\\evaluation\\fichiers\\matieres", "rb");

    if (fichierMatieres == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER matieres ***\n");
        exit(0);
    }

    fichierNotes = fopen("U:\\fichiers\\notes", "rb");

    if (fichierNotes == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER notes ***\n");
        exit(0);
    }

    edition = fopen("U:\\fichiers\\fichiersEvalStag.txt", "wt");

    if (edition == NULL)
    {
        printf("*** ERREUR OUVERTURE FICHIER fichiersEfmStag.doc ***\n");
        exit(0);
    }

/* -------------------------------------------------------------------------- */
/* Impression du fichier des stagiaires                                       */
/* -------------------------------------------------------------------------- */
    fprintf(edition, "\n\nFICHIER DES STAGIAIRES\n\n");

    fread(&stagiaire, sizeof(STAGIAIRE), 1, fichierStagiaires);

    do
    {
        fprintf(edition, "%3d %s %s\n",
                stagiaire.numero,
                stagiaire.prenom,
                stagiaire.nom);

        fread(&stagiaire, sizeof(STAGIAIRE), 1, fichierStagiaires);
    }
    while(!feof(fichierStagiaires));

/* -------------------------------------------------------------------------- */
/* Impression du fichier des matieres                                         */
/* -------------------------------------------------------------------------- */
    fprintf(edition, "\n\nFICHIER DES MATIERES\n\n");

    fread(&matiere, sizeof(MATIERE), 1, fichierMatieres);

    do
    {
        fprintf(edition, "%3d %s\n",
                matiere.numMatiere,
                matiere.nomMatiere);

        fread(&matiere, sizeof(MATIERE), 1, fichierMatieres);
    }
    while(!feof(fichierMatieres));

/* -------------------------------------------------------------------------- */
/* Impression du fichier des notes                                            */
/* -------------------------------------------------------------------------- */
    fprintf(edition, "\n\nFICHIER DES NOTES\n\n");

    fread(&note, sizeof(NOTE), 1, fichierNotes);

    do
    {
        fprintf(edition, "%3d %3d %3d\n",
                note.numStagiaire,
                note.numMatiere,
                note.note);

        fread(&note, sizeof(NOTE), 1, fichierNotes);
    }
    while(!feof(fichierNotes));

    fclose(fichierStagiaires);
    fclose(fichierMatieres);
    fclose(fichierNotes);
    fclose(edition);

    return 0;
}
