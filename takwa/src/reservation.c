#include "reservation.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
void ajouter_reservation(char *filename, reservation RS) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "ID_reservation:%s, CIN_citoyen:%s, ID_parking:%s, ID_service:%s, type_vehicule: %s, date:%02d/%02d/%04d, duree:%d, prix:%f\n",RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type,  RS.date.jj, RS.date.mm, RS.date.aaaa, RS.duree, RS.prix);
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s\n", filename);
    }
}

void modifier_reservation(char *filename, char *ID_r, reservation nouv, int *success) {
    reservation RS;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f == NULL) {
        printf("Error: Cannot open file %s for reading.\n", filename);
        return;
    }
    if (f2 == NULL) {
        printf("Error: Cannot open temp.txt for writing.\n");
        fclose(f);
        return;
    }

    int found = 0; // To check if the ID is found
    while (1) {
        int res = fscanf(f, "ID_reservation:%19[^,], CIN_citoyen:%19[^,], ID_parking:%19[^,], ID_service:%19[^,], type_vehicule:%19[^,], date:%02d/%02d/%04d, duree:%d, prix:%f\n",
                         RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type, &RS.date.jj, &RS.date.mm, &RS.date.aaaa, &RS.duree, &RS.prix);

        if (res != 10) { // Malformed line or end of file reached
            printf("Debug: fscanf returned %d. Malformed line or end of file reached.\n", res);
            break;
        }
        printf("Debug: Ligne lue : ID_res=%s, CIN=%s, ID_parking=%s, ID_service=%s, Type_vehicule=%s, Date=%02d/%02d/%04d, Duree=%d, Prix=%f\n",
               RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type, RS.date.jj, RS.date.mm, RS.date.aaaa, RS.duree, RS.prix);

        if (strcmp(RS.ID_res, ID_r) == 0) {
            found = 1;
            printf("Debug: Match found for ID_res=%s. Updating...\n", ID_r);
            // Write the updated reservation details
            fprintf(f2, "ID_reservation:%s, CIN_citoyen:%s, ID_parking:%s, ID_service:%s, type_vehicule:%s, date:%02d/%02d/%04d, duree:%d, prix:%f\n",
                    nouv.ID_res, nouv.CIN, nouv.ID_par, nouv.ID_ser, nouv.type,
                    nouv.date.jj, nouv.date.mm, nouv.date.aaaa, nouv.duree, nouv.prix);
        } else {
            // Write the existing reservation details unchanged
            fprintf(f2, "ID_reservation:%s, CIN_citoyen:%s, ID_parking:%s, ID_service:%s, type_vehicule:%s, date:%02d/%02d/%04d, duree:%d, prix:%f\n",
                    RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type,
                    RS.date.jj, RS.date.mm, RS.date.aaaa, RS.duree, RS.prix);
        }
    }

    fclose(f);
    fclose(f2);

    if (found) {
        printf("Debug: Reservation with ID_res=%s successfully updated.\n", ID_r);
        // Replace the original file with the updated file only if the reservation is found
        remove(filename);
        rename("temp.txt", filename);
        *success = 1; // Set success flag to 1 when reservation is updated
    } else {
        printf("Debug: No reservation found with ID_res=%s.\n", ID_r);
        // In case of failure, delete the temporary file
        remove("temp.txt");
        *success = 0; // Set success flag to 0 when reservation is not found
    }
}


int supprimer_reservation(char *filename, char *ID_r) {
    reservation RS;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");
    int deleted = 0;

    if (!f || !f2) {
        perror("Erreur d'ouverture des fichiers");
        if (f) fclose(f);
        if (f2) fclose(f2);
        return 0; // Impossible d'ouvrir les fichiers
    }

    printf("Debug: Fichiers ouverts avec succès.\n");

    while (1) {
        // Lire une ligne du fichier
        int res = fscanf(f, "ID_reservation:%19[^,], CIN_citoyen:%19[^,], ID_parking:%19[^,], ID_service:%19[^,], type_vehicule:%19[^,], date:%02d/%02d/%04d, duree:%d, prix:%f\n",
                         RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type,
                         &RS.date.jj, &RS.date.mm, &RS.date.aaaa, &RS.duree, &RS.prix);

        if (res == EOF) {
            printf("Debug: Fin du fichier atteinte.\n");
            break;
        } else if (res != 10) {
            printf("Erreur : Ligne mal formatée détectée, ignorée.\n");
            continue;
        }

        printf("Debug: Ligne lue : ID_res=%s, CIN=%s, ID_parking=%s, ID_service=%s, Type_vehicule=%s, Date=%02d/%02d/%04d, Duree=%d, Prix=%f\n",
               RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type,
               RS.date.jj, RS.date.mm, RS.date.aaaa, RS.duree, RS.prix);

        // Vérifier si l'ID correspond
        if (strcmp(RS.ID_res, ID_r) == 0) {
            printf("Suppression de la réservation trouvée pour l'ID %s\n", RS.ID_res);
            deleted = 1; // Indiquer qu'une ligne a été supprimée
        } else {
            // Réécrire la ligne dans le fichier temporaire
            fprintf(f2, "ID_reservation:%s, CIN_citoyen:%s, ID_parking:%s, ID_service:%s, type_vehicule:%s, date:%02d/%02d/%04d, duree:%d, prix:%f\n",
                    RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type,
                    RS.date.jj, RS.date.mm, RS.date.aaaa, RS.duree, RS.prix);
        }
    }

    fclose(f);
    fclose(f2);

    // Gérer le fichier temporaire en fonction du résultat
    if (deleted) {
        remove(filename); // Supprimer l'ancien fichier
        rename("temp.txt", filename); // Renommer le fichier temporaire
        printf("Suppression réussie de l'ID: %s\n", ID_r);
    } else {
        remove("temp.txt"); // Supprimer le fichier temporaire inutilisé
        printf("Aucun enregistrement trouvé pour la suppression de l'ID: %s\n", ID_r);
    }

    return deleted; // Retourner 1 si suppression, 0 sinon
}









int chercher_reservation(const char *filename, const char *ID_r, reservation *RS) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return 0; // Erreur d'ouverture
    }

    printf("Debug : Fichier %s ouvert avec succès\n", filename);
    printf("Debug : Recherche de l'ID_reservation : %s\n", ID_r);

    int line_number = 0;
    char temp_line[256]; // Pour stocker chaque ligne brute

    while (fgets(temp_line, sizeof(temp_line), file)) {
        line_number++;
        printf("Debug : Ligne brute %d : %s", line_number, temp_line);

        // Extraire les données avec sscanf en utilisant les étiquettes
        char ID_reservation[20], CIN[20], ID_parking[20], ID_service[20], type_vehicule[50];
        char date[20];
        int duree;
        float prix;
        int jj, mm, aaaa;

        if (sscanf(temp_line, "ID_reservation:%[^,], CIN_citoyen:%[^,], ID_parking:%[^,], ID_service:%[^,], type_vehicule: %[^,], date:%[^,], duree:%d, prix:%f",
                   ID_reservation, CIN, ID_parking, ID_service, type_vehicule, date, &duree, &prix) == 8) {
            // Parse de la date
            if (sscanf(date, "%d/%d/%d", &jj, &mm, &aaaa) != 3) {
                printf("Debug : Erreur de parsing de la date à la ligne %d\n", line_number);
                continue; // Passer à la ligne suivante
            }

            // Afficher les données extraites
            printf("Debug : Ligne %d lue correctement :\n", line_number);
        printf("Debug:Ligne lue :  ID_res=%s, CIN=%s, ID_parking=%s, ID_service=%s, Type_vehicule=%s, Date=%02d/%02d/%04d, Duree=%d, Prix=%f\n",
               RS->ID_res, RS->CIN, RS->ID_par, RS->ID_ser, RS->type, RS->date.jj, RS->date.mm, RS->date.aaaa, RS->duree, RS->prix);

            // Comparaison de l'ID_reservation avec l'ID recherché
            if (strcmp(ID_reservation, ID_r) == 0) {
                // Copier les données dans la structure `RS`
                strcpy(RS->ID_res, ID_reservation);
                strcpy(RS->CIN, CIN);
                strcpy(RS->ID_par, ID_parking);
                strcpy(RS->ID_ser, ID_service);
                strcpy(RS->type, type_vehicule);
                RS->date.jj = jj;
                RS->date.mm = mm;
                RS->date.aaaa = aaaa;
                RS->duree = duree;
                RS->prix = prix;

                printf("Debug : Réservation trouvée à la ligne %d\n", line_number);
                fclose(file);
                return 1; // Réservation trouvée
            }
        } else {
            printf("Debug : Ligne %d ignorée (format incorrect)\n", line_number);
        }
    }

    printf("Debug : Fin du fichier atteinte, ID_reservation introuvable\n");
    fclose(file);
    return 0; // Réservation non trouvée
}
GList* lire_reservations( char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    GList *reservations_list = NULL;
    char line[256];
    reservation res;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "ID_reservation:%19[^,], CIN_citoyen:%19[^,], ID_parking:%19[^,], ID_service:%19[^,], type_vehicule:%19[^,], date:%d/%d/%d, duree:%d, prix:%f",
                   res.ID_res, res.CIN, res.ID_par, res.ID_ser, res.type,
                   &res.date.jj, &res.date.mm, &res.date.aaaa, &res.duree, &res.prix) != 9) {
            g_print("Erreur de format dans la ligne : %s\n", line);
            continue;  // Skip incorrect line
        }
        reservations_list = g_list_append(reservations_list, g_memdup(&res, sizeof(res)));
    }

    fclose(file);
    return reservations_list;
}



// Fonction pour afficher les données dans un TreeView
void afficher_reservation(GtkWidget *treeview, char *filename) {
    GtkListStore *store;
    GtkTreeIter iter;
    reservation RS;
    FILE *f = fopen(filename, "r");

    if (!f) {
        printf("Error: Cannot open file %s for reading.\n", filename);
        return;
    }

    printf("Debug: Opened file %s for reading.\n", filename);

    store = gtk_list_store_new(8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT );
   
    while (1) {
        int res = fscanf(f, "ID_reservation:%19[^,], CIN_citoyen:%19[^,], ID_parking:%19[^,], ID_service:%19[^,], type_vehicule: %19[^,], date:%02d/%02d/%04d, duree:%d, prix:%f\n",
                         RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type, &RS.date.jj, &RS.date.mm, &RS.date.aaaa, &RS.duree, &RS.prix);
        
        if (res <= 0) { // If fscanf fails, break the loop
            break;
        }
        printf("Debug: Ligne lue : ID_res=%s, CIN=%s, ID_parking=%s, ID_service=%s, Type_vehicule=%s, Date=%02d/%02d/%04d, Duree=%d, Prix=%f\n",
               RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type, RS.date.jj, RS.date.mm, RS.date.aaaa, RS.duree, RS.prix);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, RS.ID_res,
                           1, RS.CIN,
                           2, RS.ID_par,
                           3, RS.ID_ser,
                           4, RS.type,
                           5,g_strdup_printf("%02d/%02d/%04d", RS.date.jj, RS.date.mm, RS.date.aaaa),
                           6,RS.duree,
                           7, RS.prix,
                           -1);
    }

    if (feof(f)) {
        printf("Debug: End of file reached.\n");
    } else if (ferror(f)) {
        printf("Debug: Error reading file %s.\n", filename);
    }

    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
        GtkCellRenderer *renderer;
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "ID Réservation", renderer, "text", 0, NULL);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "CIN", renderer, "text", 1, NULL);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "ID Parking", renderer, "text", 2, NULL);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "ID Service", renderer, "text", 3, NULL);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "Type", renderer, "text", 4, NULL);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "Date", renderer, "text", 5, NULL);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "Durée", renderer, "text", 6, NULL);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_insert_column_with_attributes(treeview, -1, "Prix", renderer, "text", 7, NULL);
       

}






