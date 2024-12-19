#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "parking.h"
#include <gtk/gtk.h>
#include "reservation.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"
reservation RS;
void on_checkbutton1_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{   
    if (gtk_toggle_button_get_active(togglebutton))
      {strcpy(RS.type,"Camion");}

}

void on_checkbutton2_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
     if (gtk_toggle_button_get_active(togglebutton))
      {strcpy(RS.type, "Voiture");}
}


void on_checkbutton3_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{ 
      if (gtk_toggle_button_get_active(togglebutton))
      {strcpy(RS.type,"Moto");}
}
void on_buttonajouter_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *entry1 = lookup_widget(button, "entry1");
    GtkWidget *entry2 = lookup_widget(button, "entry2");
    GtkWidget *entry3 = lookup_widget(button, "entry3");
    GtkWidget *entry4 = lookup_widget(button, "entry4");
    GtkWidget *entry5 = lookup_widget(button, "entry5");
    GtkWidget *spinbutton1 = lookup_widget(button, "spinbutton1");
    GtkWidget *spinbutton2 = lookup_widget(button, "spinbutton2");
    GtkWidget *spinbutton3 = lookup_widget(button, "spinbutton3");
    GtkWidget *combobox1 = lookup_widget(button, "combobox1");
    
    strcpy(RS.ID_res, gtk_entry_get_text(GTK_ENTRY(entry1)));
    strcpy(RS.CIN, gtk_entry_get_text(GTK_ENTRY(entry2)));
    strcpy(RS.ID_par, gtk_entry_get_text(GTK_ENTRY(entry3)));
    strcpy(RS.ID_ser, gtk_entry_get_text(GTK_ENTRY(entry4)));
    RS.date.jj = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton1));
    RS.date.mm = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton2));
    RS.date.aaaa = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton3));
    char *selected_duree[20];
    strcpy(selected_duree , gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1)));
    RS.duree = atoi(selected_duree);
    char prix[20];
    strcpy(prix, gtk_entry_get_text(GTK_ENTRY(entry5)));
    RS.prix = atof(prix);  // Convertir le prix en float
    
    ajouter_reservation("reservation.txt", RS);
}



void on_buttonAnnuler_clicked (GtkButton *button, gpointer user_data)
{
    gtk_main_quit();
}


// Global variable to store the selected vehicle type
char vehicule[20] = "";

void on_checkbutton4_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(vehicule, "Camion");
        printf("Vehicule set to: %s\n", vehicule);
    }
}

void on_checkbutton5_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(vehicule, "Voiture");
        printf("Vehicule set to: %s\n", vehicule);
    }
}

void on_checkbutton6_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(vehicule, "Moto");
        printf("Vehicule set to: %s\n", vehicule);
    }
}



void on_button2_clicked (GtkButton *button, gpointer user_data)
{
     gtk_main_quit();
}

void on_buttonmodifier_clicked(GtkWidget *button, gpointer user_data) {
    reservation nouv;
    GtkWidget *dialog;
    int success = 0;

    // Debugging start
    printf("Debug: on_buttonmodifier_clicked called.\n");

    GtkWidget *entry9 = lookup_widget(button, "entry9");
    GtkWidget *entry10 = lookup_widget(button, "entry10");
    GtkWidget *entry11 = lookup_widget(button, "entry11");
    GtkWidget *entry12 = lookup_widget(button, "entry12");
    GtkWidget *entry13 = lookup_widget(button, "entry13");
    GtkWidget *spinbutton5 = lookup_widget(button, "spinbutton5");
    GtkWidget *spinbutton6 = lookup_widget(button, "spinbutton6");
    GtkWidget *spinbutton7 = lookup_widget(button, "spinbutton7");
    GtkWidget *combobox2 = lookup_widget(button, "combobox2");

    strcpy(nouv.ID_res, gtk_entry_get_text(GTK_ENTRY(entry9)));
    strcpy(nouv.CIN, gtk_entry_get_text(GTK_ENTRY(entry10)));
    strcpy(nouv.ID_par, gtk_entry_get_text(GTK_ENTRY(entry11)));
    strcpy(nouv.ID_ser, gtk_entry_get_text(GTK_ENTRY(entry12)));

    nouv.date.jj = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton5));
    nouv.date.mm = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton6));
    nouv.date.aaaa = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton7));
    char *selected_duree[20];
    strcpy(selected_duree ,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox2)));
    nouv.duree = atoi(selected_duree);

    char prix[20];
    strcpy(prix, gtk_entry_get_text(GTK_ENTRY(entry13)));
    nouv.prix = atoi(prix);

    strcpy(nouv.type, vehicule);

    // Print debugging information
    printf("Debug: New reservation details:\n");
    printf("  ID_res=%s, CIN=%s, ID_par=%s, ID_ser=%s, duree=%d, prix=%f, vehicule=%s\n",
           nouv.ID_res, nouv.CIN, nouv.ID_par, nouv.ID_ser, nouv.duree, nouv.prix, nouv.type);

    // Display confirmation dialog
    dialog = gtk_message_dialog_new(GTK_WINDOW(user_data),
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_YES_NO,
                                    "Êtes-vous sûr de vouloir modifier cette réservation ?");
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (response == GTK_RESPONSE_YES) {
        // Call the function to modify the reservation
        modifier_reservation("reservation.txt", nouv.ID_res, nouv, &success);

        // Display success or error dialog
        if (success) {
            dialog = gtk_message_dialog_new(GTK_WINDOW(user_data),
                                            GTK_DIALOG_MODAL,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "Réservation modifiée avec succès !");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } else {
            dialog = gtk_message_dialog_new(GTK_WINDOW(user_data),
                                            GTK_DIALOG_MODAL,
                                            GTK_MESSAGE_ERROR,
                                            GTK_BUTTONS_OK,
                                            "La modification a échoué ! Essayez plus tard.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        // User clicked "No", do nothing
        printf("Modification annulée par l'utilisateur.\n");
    }
}



void on_buttonchercher_clicked(GtkWidget *button, gpointer user_data) {
    char ID_r[20];
    char result_text[500];
    reservation RS; // Structure de réservation
    int var;
    GtkWidget *entry14 = lookup_widget(button, "entry14");
    GtkWidget *label_RESULT = lookup_widget(button, "label_RESULT");
    
    strcpy(ID_r, gtk_entry_get_text(GTK_ENTRY(entry14)));  // Récupération de l'ID
    printf("Debug : ID_r=%s\n", ID_r);
    var = chercher_reservation("reservation.txt", ID_r, &RS); // Recherche de la réservation
    
    if (var == 1) {
        snprintf(result_text, sizeof(result_text),
                 "Réservation trouvée :\n"
                 "ID_res : %s\nCIN_citoyen : %s\nID_parking : %s\nID_service : %s\n"
                 "Type_vehicule : %s\nDate : %02d/%02d/%04d\nDuree : %d\nPrix : %f\n",
                 RS.ID_res, RS.CIN, RS.ID_par, RS.ID_ser, RS.type,
                 RS.date.jj, RS.date.mm, RS.date.aaaa, RS.duree, RS.prix);
    } else if (var == 0) {
        snprintf(result_text, sizeof(result_text), "Réservation introuvable pour l'ID_reservation : %s", ID_r);
    }
    
    gtk_label_set_text(GTK_LABEL(label_RESULT), result_text); // Affichage des données ou message
}



void on_buttonannulerch_clicked  (GtkWidget *button, gpointer user_data)
{
   gtk_main_quit();
}


void on_buttonsupprimer_clicked(GtkWidget *button, gpointer user_data) {
    char ID_r[20];
    int value;
    GtkWidget *entry15 = lookup_widget(button, "entry15");
    GtkWidget *dialog;
    GtkResponseType response;
    
    // Récupérer l'ID de la réservation à supprimer
    strcpy(ID_r, gtk_entry_get_text(GTK_ENTRY(entry15))); 

    // Vérifier si la réservation existe
    value = chercher_reservation("reservation.txt", ID_r, &RS);

    if (value == 1) {
        // Créer un dialogue de confirmation
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_QUESTION,
                                        GTK_BUTTONS_YES_NO,
                                        "Voulez-vous vraiment supprimer la réservation avec l'ID : %s ?", ID_r);

        // Afficher le dialogue et attendre la réponse
        response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        if (response == GTK_RESPONSE_YES) {
            // Supprimer la réservation si l'utilisateur a confirmé
            if (supprimer_reservation("reservation.txt", ID_r) == 1) {
                dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "La réservation a été supprimée avec succès.");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
            } else {
                // Erreur lors de la suppression
                dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "Erreur : Impossible de supprimer la réservation.");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
            }
        }
    } else {
        // Afficher un message si la réservation n'existe pas
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_WARNING,
                                        GTK_BUTTONS_OK,
                                        "La réservation avec l'ID : %s est introuvable.", ID_r);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}
void on_buttonactualiser_clicked(GtkWidget *button, gpointer user_data) {
    g_debug("Debug: on_buttonactualiser_clicked called."); // Debug info
    GtkWidget *treeview2 = lookup_widget(button, "treeview2");
    afficher_reservation(treeview2, "reservation.txt");


}

void on_buttonsupprimerR_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *notebook_widget = lookup_widget(button, "notebook1");
    gtk_notebook_set_current_page(notebook_widget, 2); 
}

void on_buttonmodifierR_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *notebook_widget = lookup_widget(button, "notebook1");
    gtk_notebook_set_current_page(notebook_widget, 1); 
}

void on_buttonchercherR_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *notebook_widget = lookup_widget(button, "notebook1");
    gtk_notebook_set_current_page(notebook_widget, 3);  
    
}

void on_buttonafficherR_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *notebook_widget = lookup_widget(button, "notebook1");
    gtk_notebook_set_current_page(notebook_widget, 4); 
}

void on_buttonajouterR_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *notebook_widget = lookup_widget(button, "notebook1");
    gtk_notebook_set_current_page(notebook_widget, 0); 
}

void
on_buttonactualiserP_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
    g_debug("Debug: on_buttonactualiserP_clicked called."); // Debug info
    GtkWidget *treeview3 = lookup_widget(button, "treeview3");
    afficher_parkings_trie(treeview3, "parking.txt");

}

