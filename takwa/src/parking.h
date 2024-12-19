#include <stdio.h>
#include <gtk/gtk.h>
typedef struct{
    int idparking;
    int availability;
}parking;
void parking_tries(char *filename);
void afficher_parkings_trie(GtkTreeView *treeview,  char *filename);
