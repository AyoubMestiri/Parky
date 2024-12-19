#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "agent.h"
#include<stdio.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <string.h>
#include <gtk/gtk.h>

int ajouterAgent(char* filename, Agent A)
{
    FILE  * f=fopen(filename,"a");
    if(f!=NULL)
    {
    fprintf(f,"%s  %s  %s  %s %s %s\n",A.id,A.nom,A.prenom,A.email,A.type_Ag,A.sexe);
    fclose(f);
    return 1;
    }
    else return 0;
}
int modifierAgent(char * filename, char id[50], Agent nouv)
{
    int tr=0;
    Agent A;
    FILE * f=fopen(filename,"r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %s %s\n",A.id,A.nom,A.prenom,A.email,A.type_Ag,A.sexe)!=EOF)
        {
            if(strcmp(A.id,id)==0)
            {
                fprintf(f2,"%s %s %s %s %s %s\n",nouv.id,nouv.nom,nouv.prenom,nouv.email,nouv.type_Ag,nouv.sexe);
                tr=1;
            }
            else
                fprintf(f2,"%s %s %s %s %s %s\n",A.id,A.nom,A.prenom,A.email,A.type_Ag,A.sexe);
         }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt",filename);
    return tr;
}
int supprimerAgent(char *filename , char id[50])
{
    int tr=0;
    Agent A;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt","w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %s %s\n",A.id,A.nom,A.prenom,A.email,A.type_Ag,A.sexe)!=EOF)
        {
            if(strcmp(A.id,id)==0)
                tr=1;
            else
               fprintf(f2,"%s %s %s %s %s %s\n",A.id,A.nom,A.prenom,A.email,A.type_Ag,A.sexe);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt",filename);
    return tr;
}
void afficherAgent(char *filename)
{
    Agent A;
    FILE * f=fopen(filename,"r");
    if(f!=NULL)
    {
       while( fscanf(f,"%s %s %s %s %s %s\n",A.id,A.nom,A.prenom,A.email,A.type_Ag,A.sexe)!=EOF)
          {
              printf("identifiant d'agent : %s\n",A.id);
              printf("nom d'agent : %s\n",A.nom);
              printf("prenom d'agent : %s\n",A.prenom);
              printf("email d'agent: %s\n",A.email);
              printf("type d'agent: %s\n",A.type_Ag);
              printf("sexe d'agent: %s\n",A.sexe);
          }

    }
}
void afficherReservationsParDate(GtkWidget *treeview1, char*l,char * dat)
{

GtkListStore *adstore;/*creation du modele de type liste*/
adstore=NULL;
GtkTreeViewColumn *adcolumn;/*visualisation des colonnes*/
GtkCellRenderer *cellad;/*afficheur de cellule(text,image..)*/

FILE *f;
adstore=gtk_tree_view_get_model(treeview1);



	char ID_res [20];
	char CIN[20];
	char ID_par [20];
	char ID_ser [20];
	char type_vehicule[20];
	char date[50];
	char duree[50];
        char prix[10];

     
     

	/* Creation de la 1ere colonne */
	if(adstore==NULL)
	{cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("ID_res",
                                                            cellad,
                                                            "text", 0,
                                                            NULL);


        /* Ajouter la 1er colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);


	/* Creation de la 2eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("CIN",
                                                            cellad,
                                                            "text", 1,
                                                            NULL);
	/* Ajouter la 2emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);




	/* Creation de la 4eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("ID_par",
                                                            cellad,
                                                            "text", 2,
                                                            NULL);
	/* Ajouter la 4emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 5eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("ID_ser",
                                                            cellad,
                                                            "text", 3,
                                                            NULL);
	/* Ajouter la 5emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);


        /* Creation de la 5eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("type_vehicule",
                                                            cellad,
                                                            "text", 4,
                                                            NULL);
	/* Ajouter la 5emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 3eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("date",
                                                            cellad,
                                                            "text", 5,
                                                            NULL);

	/* Ajouter la 3emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 3eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("duree",
                                                            cellad,
                                                            "text", 6,
                                                            NULL);

	/* Ajouter la 3emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 3eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("prix",
                                                            cellad,
                                                            "text", 7,
                                                            NULL);

	/* Ajouter la 3emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);


	}
   /* Creation du modele */
        adstore = gtk_list_store_new(8,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING);
   /* Insertion des elements */
        f=fopen(l,"r");
while(fscanf(f,"%s %s %s %s %s %s %s %s\n",ID_res,CIN,ID_par,ID_ser,type_vehicule,date,duree,prix)!= EOF)
        {if(strcmp(date,dat)==0){
	  GtkTreeIter pIter;

         /* Creation de la nouvelle ligne */
         gtk_list_store_append(adstore, &pIter);
         /* Mise a jour des donnees */
         gtk_list_store_set(adstore, &pIter,
                            0,ID_res,
                            1,CIN,
                            2,ID_par,
                            3,ID_ser,
                            4,type_vehicule,
			    5,date,
			    6,duree,
			    7,prix,
                            -1);}}
        fclose(f);


 	gtk_tree_view_set_model ( GTK_TREE_VIEW (treeview1),
                                  GTK_TREE_MODEL(adstore)  );
g_object_unref(adstore);
}


Agent chercherAgent(char *filename, char id[50])

    {
    Agent A;
    int tr;
    FILE * f=fopen("agent.txt", "r");
     tr=0;
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%s %s %s %s %s %s\n",A.id,A.nom,A.prenom,A.email,A.type_Ag,A.sexe)!=EOF)
        {
            if(strcmp(A.id,id)==0)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        strcpy(A.id,"-1");
    return A;}




