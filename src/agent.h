#ifndef agent_h
#define agent_h
#include <gtk/gtk.h>

typedef struct{
    char id[50];
    char nom[50];
    char prenom[50];
    char email[50];
    char type_Ag[20];  //ex:"Affecté" ou "Non Afeecté"
    char sexe[10];
} Agent;
typedef struct{
	char ID_res [20];
	char CIN[20];
	char ID_par [20];
	char ID_ser [20];
	char type_vehicule[20];
	char date[50];
	char duree[50];
        char prix[10];
}reservation;

int  ajouterAgent(char *,Agent A);
int  modifierAgent(char *, char id[50],Agent nouv);
int  supprimerAgent(char *,char id[50]);
void  afficherAgent(char *);
void  afficherReservationsParDate(GtkWidget *treeview1, char*l, char * dat);
Agent chercherAgent(char *,char[50]);
#endif
