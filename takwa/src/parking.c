#include "parking.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void parking_tries(char *filename) {
    parking parkings[20];
    int count = 0;
    int i, j;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("parkingtriee.txt", "w");

    if (f == NULL || f2 == NULL) {
        printf("\nErreur : Impossible d'ouvrir un des fichiers\n");
        return;
    }

    // Lire les données du fichier
    while (fscanf(f, "%d;%d\n", &parkings[count].idparking, &parkings[count].availability) != EOF) {
        count++;
        if (count >= 20) break; // Limiter pour ne pas dépasser la taille du tableau
    }

    printf("Debug: Nombre total de parkings lus: %d\n", count);

    // Tri des parkings par disponibilité décroissante
    printf("Debug: Début du tri des parkings par disponibilité...\n");
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (parkings[i].availability < parkings[j].availability) {
                parking temp = parkings[i];
                parkings[i] = parkings[j];
                parkings[j] = temp;
            }
        }
    }

    printf("Debug: Tri terminé.\n");

    // Écriture des parkings triés
    printf("Debug: Écriture des parkings triés dans parkingtriee.txt...\n");
    for (i = 0; i < count; i++) {
        fprintf(f2, "%d;%d\n", parkings[i].idparking, parkings[i].availability);
    }

    fclose(f);
    fclose(f2);

    printf("Debug: Remplacement du fichier original par le fichier trié...\n");
    remove(filename);
    rename("parkingtriee.txt", filename);
    printf("Debug: Opération terminée.\n");
}

void afficher_parkings_trie(GtkTreeView *treeview, char *filename) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    parking p;

    printf("Debug: Appel de parking_tries...\n");
    parking_tries(filename);  // Tri effectué ici

    printf("Debug: Création du modèle pour le TreeView...\n");
    store = gtk_list_store_new(2, G_TYPE_INT,    // ID Parking
                                G_TYPE_INT);     // Disponibilité

    printf("Debug: Ouverture du fichier trié : %s...\n", filename);
    f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return;
    }

    printf("Debug: Lecture des données depuis %s...\n", filename);
    while (fscanf(f, "%d;%d\n", &p.idparking, &p.availability) != EOF) {
        printf("Debug: Parking lu - ID: %d, Disponibilité: %d\n", p.idparking, p.availability);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, p.idparking,
                           1, p.availability,
                           -1);
    }
    fclose(f);

    printf("Debug: Association du modèle au TreeView...\n");
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);

    printf("Debug: Configuration des colonnes pour le TreeView...\n");
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID Parking", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Disponibilité", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    printf("Debug: Affichage des parkings terminé.\n");
}
