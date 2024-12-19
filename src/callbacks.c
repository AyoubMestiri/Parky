#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "agent.h"
#include <string.h>

int Sexe;
int Sexe1;

void
on_Aj_clicked                          (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *combobox1, *entry_id, *entry_nom, *entry_prenom, *entry_email,*entry_type, *Homme, *Femme,*Aj;  
    Agent a;
    combobox1=lookup_widget(button,"comboboxentry1");
    Aj=lookup_widget(button,"Aj");
    entry_id = lookup_widget(button, "entry_id");         
    entry_nom = lookup_widget(button, "entry_Nom");       
    entry_prenom = lookup_widget(button, "entry_pre"); 
    entry_email = lookup_widget(button, "entry_em");   
    entry_type = lookup_widget(button, "entry_tp");

    strcpy(a.id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    strcpy(a.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(a.prenom, gtk_entry_get_text(GTK_ENTRY(entry_prenom)));
    strcpy(a.email, gtk_entry_get_text(GTK_ENTRY(entry_email)));
    strcpy(a.type_Ag, gtk_entry_get_text(GTK_ENTRY(entry_type)));

    if (Sexe==1)
    strcpy(a.sexe,"Homme");
    if (Sexe==2)
    strcpy(a.sexe,"Femme");
    ajouterAgent("agent.txt",a);
    
}



void
on_Femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
  {Sexe=2;}
}


void
on_Homme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
 {Sexe=1;}
}



void
on_Md_clicked                          (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *comboboxent, *id, *nom, *prenom, *email, *type;
    Agent nouv;
    char ide[50];
    comboboxent=lookup_widget(button,"comboboxentry1");
    id=lookup_widget(button,"entry_nvid");
    nom=lookup_widget(button,"entry_nvnm");
    prenom=lookup_widget(button,"entry_nvpr");
    email=lookup_widget(button,"entry_nvem");
    type=lookup_widget(button,"entry_nvtp");

    strcpy(nouv.id,gtk_entry_get_text(GTK_ENTRY(id)));
    strcpy(nouv.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(nouv.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
    strcpy(nouv.email,gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(nouv.type_Ag,gtk_entry_get_text(GTK_ENTRY(type)));

    if (Sexe1==1)
    strcpy(nouv.sexe,"Homme");
    if (Sexe1==2)
    strcpy(nouv.sexe,"Femme");

    strcpy(ide,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxent)));

    

    modifierAgent("agent.txt",ide,nouv);
    


}


void
on_act1_clicked                        (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *comboboxent;
    Agent nouv;
    comboboxent = lookup_widget(button, "comboboxentry1");

    // Open the file for reading
    FILE *f = fopen("agent.txt", "r");
    if (f != NULL) {
        // Loop through each entry in the file
        while ((fscanf(f, "%s %s %s %s %s %s", nouv.id, nouv.nom, nouv.prenom, nouv.email, nouv.type_Ag, nouv.sexe)) != EOF) {
            // Check if the ID already exists in the combo box
            gboolean id_exists = FALSE;
            GSList *items = gtk_combo_box_get_model(GTK_COMBO_BOX(comboboxent)); 
            GtkTreeIter iter;

            // Iterate through the model to check if the ID exists
            if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(items), &iter)) {
                do {
                    gchar *existing_id;
                    gtk_tree_model_get(GTK_TREE_MODEL(items), &iter, 0, &existing_id, -1);
                    if (g_strcmp0(existing_id, nouv.id) == 0) {
                        id_exists = TRUE;
                        g_free(existing_id);  // Free the existing ID string
                        break;
                    }
                    g_free(existing_id);  // Free the existing ID string
                } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(items), &iter));
            }

            // Append the ID only if it does not exist in the ComboBox
            if (!id_exists) {
                gtk_combo_box_append_text(GTK_COMBO_BOX(comboboxent), nouv.id);
            }
        }

        fclose(f);
    }
}


void
on_act2_clicked                        (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *comboboxent;
    Agent nouv;
    comboboxent = lookup_widget(button, "comboboxentry2");

    // Open the file for reading
    FILE *f = fopen("agent.txt", "r");
    if (f != NULL) {
        // Loop through each entry in the file
        while ((fscanf(f, "%s %s %s %s %s %s", nouv.id, nouv.nom, nouv.prenom, nouv.email, nouv.type_Ag, nouv.sexe)) != EOF) {
            // Check if the ID already exists in the combo box
            gboolean id_exists = FALSE;
            GSList *items = gtk_combo_box_get_model(GTK_COMBO_BOX(comboboxent)); 
            GtkTreeIter iter;

            // Iterate through the model to check if the ID exists
            if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(items), &iter)) {
                do {
                    gchar *existing_id;
                    gtk_tree_model_get(GTK_TREE_MODEL(items), &iter, 0, &existing_id, -1);
                    if (g_strcmp0(existing_id, nouv.id) == 0) {
                        id_exists = TRUE;
                        g_free(existing_id);  // Free the existing ID string
                        break;
                    }
                    g_free(existing_id);  // Free the existing ID string
                } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(items), &iter));
            }

            // Append the ID only if it does not exist in the ComboBox
            if (!id_exists) {
                gtk_combo_box_append_text(GTK_COMBO_BOX(comboboxent), nouv.id);
            }
        }

        fclose(f);
    }
}


void
on_Sup_clicked                         (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *dd;
char idd[20];

dd=lookup_widget(button,"comboboxentry2");
strcpy(idd,gtk_combo_box_get_active_text(GTK_COMBO_BOX(dd)));
	

    supprimerAgent("agent.txt",idd);


}


void
on_act3_clicked                        (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *comboboxent;
    Agent nouv;
    comboboxent = lookup_widget(button, "comboboxentry3");

    // Open the file for reading
    FILE *f = fopen("agent.txt", "r");
    if (f != NULL) {
        // Loop through each entry in the file
        while ((fscanf(f, "%s %s %s %s %s %s", nouv.id, nouv.nom, nouv.prenom, nouv.email, nouv.type_Ag, nouv.sexe)) != EOF) {
            // Check if the ID already exists in the combo box
            gboolean id_exists = FALSE;
            GSList *items = gtk_combo_box_get_model(GTK_COMBO_BOX(comboboxent)); 
            GtkTreeIter iter;

            // Iterate through the model to check if the ID exists
            if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(items), &iter)) {
                do {
                    gchar *existing_id;
                    gtk_tree_model_get(GTK_TREE_MODEL(items), &iter, 0, &existing_id, -1);
                    if (g_strcmp0(existing_id, nouv.id) == 0) {
                        id_exists = TRUE;
                        g_free(existing_id);  // Free the existing ID string
                        break;
                    }
                    g_free(existing_id);  // Free the existing ID string
                } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(items), &iter));
            }

            // Append the ID only if it does not exist in the ComboBox
            if (!id_exists) {
                gtk_combo_box_append_text(GTK_COMBO_BOX(comboboxent), nouv.id);
            }
        }

        fclose(f);
    }
}


void
on_act4_clicked                        (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *comboboxent;
    reservation nouv;
    comboboxent = lookup_widget(objet, "comboboxentry4");

    // Open the file for reading
    FILE *f = fopen("reservation.txt", "r");
    if (f != NULL) {
        // Loop through each entry in the file
        while ((fscanf(f, "%s %s %s %s %s %s %s %s\n", nouv.ID_res, nouv.CIN, nouv.ID_par, nouv.ID_ser, nouv.type_vehicule, nouv.date,nouv.duree,nouv.prix)) != EOF) {
            // Check if the date already exists in the combo box
            gboolean date_exists = FALSE;
            GSList *items = gtk_combo_box_get_model(GTK_COMBO_BOX(comboboxent)); 
            GtkTreeIter iter;

            // Iterate through the model to check if the date exists
            if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(items), &iter)) {
                do {
                    gchar *existing_date;
                    gtk_tree_model_get(GTK_TREE_MODEL(items), &iter, 0, &existing_date, -1);
                    if (g_strcmp0(existing_date, nouv.date) == 0) {
                        date_exists = TRUE;
                        g_free(existing_date);  // Free the existing ID string
                        break;
                    }
                    g_free(existing_date);  // Free the existing ID string
                } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(items), &iter));
            }

            // Append the ID only if it does not exist in the ComboBox
            if (!date_exists) {
                gtk_combo_box_append_text(GTK_COMBO_BOX(comboboxent), nouv.date);
            }
        }

        fclose(f);
    }

}


void
on_AcRes_clicked                       (GtkWidget       *objet,
                                        gpointer         user_data)
{

GtkTreeModel     *model;
        GtkTreeSelection *selection;
        GtkTreeIter iter;
	char dat[20];
        GtkWidget *labeldat,*p;
	p=lookup_widget(objet,"treeview1");
	labeldat=lookup_widget(objet,"comboboxentry4");

	strcpy(dat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(labeldat)));

	gchar *id_reservation;
        gchar *cin;
        gchar *id_parking;
        gchar *id_service;
  	gchar *type_voiture;
        gchar *date;
	gchar *duree;
        gchar *prix;
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(p));
        if (gtk_tree_selection_get_selected(selection, &model, &iter))
        {  gtk_tree_model_get (model,&iter,0,&id_reservation,1,&cin,2,&id_parking,3,&id_service,4,&type_voiture,5,&date,6,&duree,7,&prix,-1);
  	
               	
}
afficherReservationsParDate(p,"reservation.txt",dat);
}


void
on_Aff_clicked                         (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *comboboxent,*nm ,*pr ,*em ,*tp ,*sx;
char idd[20];
FILE *f;
int x=-1;
Agent nouv;
	nm = lookup_widget(objet,"nm");
	pr = lookup_widget(objet,"pr");
	em = lookup_widget(objet,"em");
	tp = lookup_widget(objet,"tp");
	sx = lookup_widget(objet,"sx");
        comboboxent=lookup_widget(objet,"comboboxentry3");




strcpy(idd,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxent)));

f = fopen ("agent.txt", "r");

if (f!=NULL)
 {
  while((fscanf(f,"%s %s %s %s %s %s",nouv.id,nouv.nom,nouv.prenom,nouv.email,nouv.type_Ag,nouv.sexe))!=EOF)
  {
  
    if (strcmp (idd,nouv.id) == 0)
      {
      x=1;
      } 
     } 
    
     fclose (f);
  }

if(x==-1)
{
gtk_label_set_text(GTK_LABEL(nm),"Agent inexistant");
}else
{
        Agent A= chercherAgent("agent.txt",idd);
	gtk_label_set_text(GTK_LABEL(nm),A.nom);
	gtk_label_set_text(GTK_LABEL(pr),A.prenom);
	gtk_label_set_text(GTK_LABEL(em),A.email);
	gtk_label_set_text(GTK_LABEL(tp),A.type_Ag);
        gtk_label_set_text(GTK_LABEL(sx),A.sexe);
}
}

void
on_Homme1_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
  {Sexe1=1;}
}


void
on_Femme1_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) 
  {Sexe1=2;}
}

