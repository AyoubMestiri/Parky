#include <stdio.h>
#include <gtk/gtk.h>
typedef struct {
    int jj;
    int mm;
    int aaaa;
} Date;

typedef struct {
    char ID_res[20];
    char CIN[20];
    char ID_par[20];
    char ID_ser[20];
    char type[20];
    Date date;
    int duree;
    float prix;
} reservation;

void ajouter_reservation(char *filename, reservation RS);
GList* lire_reservations( char *filename);
void modifier_reservation(char *filename, char *ID_r, reservation nouv, int *success);
int supprimer_reservation(char *filename, char *ID_r);
void afficher_reservation(GtkWidget *treeview, char *filename);
int chercher_reservation(const char *filename, const char *ID_r, reservation *RS);
