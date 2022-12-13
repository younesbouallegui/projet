#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "election.h"

int x,y;
char Tpe[20];
char Nbh[20];
char Nbf[20];

void
on_radiobutton1_nbr1_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=1;}
}

void
on_radiobutton1_nbr2_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=2;}
}

void
on_radiobutton1_nbr3_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=3;}
}

void
on_radiobutton1_nbr4_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=4;}
}

void
on_radiobutton1_nbr5_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=5;}
}


void
on_radiobutton1_nbr6_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=6;}
}

void
on_radiobutton1_nbr7_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{x=7;}
}

void
on_checkbutton1_confi_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
{y=1;}
}


void
on_button1_ajouterElection_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
election e;
GtkWidget *windowajout, *windowelection,*id,*jour,*mois,*annee,*gou,*munic,*nbrh,*nbrc,*output,*output1;
windowajout=create_window_ajouter_election();
windowelection=create_window_election();
id = lookup_widget(button,"entry1_ideclection");
gou= lookup_widget(button,"entry1_gouvernorat");
jour = lookup_widget(button,"spinbutton1_jour");
mois = lookup_widget(button,"spinbutton1_mois");
annee = lookup_widget(button,"spinbutton1_annee");
munic=lookup_widget(button,"comboboxentry1_munic");
strcpy(e.identifiant,gtk_entry_get_text(GTK_ENTRY(id)));
strcpy(e.gouvernorat,gtk_entry_get_text(GTK_ENTRY(gou)));
e.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jour));
e.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (mois));
e.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (annee));
strcpy(e.municipalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(munic)));
if(x==1 )
{strcpy(e.nbhabit,"5000");
e.nbcons=12;
} 
else if(x==2)
{strcpy(e.nbhabit,"5001->10000");
e.nbcons=16;
}
else if(x==3)
{strcpy(e.nbhabit,"10001->25000");
e.nbcons=22;
}
else if(x==4)
{strcpy(e.nbhabit,"25001->50000");
e.nbcons=30;
}
else if(x==5)
{strcpy(e.nbhabit,"50001->100000");
e.nbcons=36;
}
else if(x==7)
{strcpy(e.nbhabit,"100001->500000");
e.nbcons=40;
}
else if(x==6)
{strcpy(e.nbhabit,"Plus500000");
e.nbcons=60;
}
if(y==1){
if ((strcmp(e.identifiant,"")==0)||( strcmp(e.gouvernorat,"")==0)||( strcmp(e.municipalite,"")==0)) {
output=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output), "Données manquantes. \n Veuillez remplir tout les champs!");
output1=lookup_widget(button,"label1_ajouter");
gtk_label_set_text(GTK_LABEL(output1), "");
}
else
{int k;

k=rechercher_election(e.identifiant);
if(k==1){output=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output), "id est deja existe");}
else{
ajouter_election(e);
output=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output), "");
output1=lookup_widget(button,"label1_ajouter");
gtk_label_set_text(GTK_LABEL(output1), "Ajouter avec Succes");
}}}
x=0;
y=0;


}


void
on_button1_retourajt_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowajouter, *menu_election;
windowajouter=lookup_widget(button,"window_ajouter_election");
gtk_widget_destroy(windowajouter);
menu_election=create_menu_election();
gtk_widget_show (menu_election);
}


void
on_treeview1_affElection_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* id;
gchar* jour;
gchar* mois;
gchar* annee;
gchar* gou;
gchar* muni;
gchar* nbh;
gchar* nbc;
election e;
GtkTreeModel *model= gtk_tree_view_get_model(treeview);
GtkWidget* windowajout,*windowelection,*tre,*idd,*jj,*mm,*aa,*go,*mu,*nh,*nc;

if (gtk_tree_model_get_iter(model, &iter,path))
{


gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,1,&jour,2,&mois,3,&annee,4,&gou,5,&muni,6,&nbh,7,&nbc,-1);

windowajout=create_window_ajouter_election();
windowelection=create_window_election();
gtk_widget_hide(windowelection);
gtk_widget_show(windowajout);

idd=lookup_widget(windowajout,"entry1_ideclection");
gtk_entry_set_text(GTK_ENTRY(idd),id);

jj=lookup_widget(windowajout,"spinbutton1_jour");
gtk_entry_set_text(GTK_ENTRY(jj),jour);

mm=lookup_widget(windowajout,"spinbutton1_mois");
gtk_entry_set_text(GTK_ENTRY(mm),mois);

aa=lookup_widget(windowajout,"spinbutton1_annee");
gtk_entry_set_text(GTK_ENTRY(aa),annee);

go=lookup_widget(windowajout,"entry1_gouvernorat");
gtk_entry_set_text(GTK_ENTRY(go),gou);
/*
mu=lookup_widget(windowajout,"comboboxentry1_munic");
gtk_combo_box_new_text(GTK_ENTRY(mu),muni);
*/


}
}


void
on_button2_windAjouter_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);

}


void
on_button2_windModif_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);
}


void
on_button2_rechElect_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_rech, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_rech=create_window_recherelect ();
gtk_widget_show (window_rech);
}


void
on_button2_SuppElect_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
int k;
char identi[20];
GtkWidget *windowElection,*tree, *iden,*output;
iden = lookup_widget(button,"entry2_SuppELect");
strcpy(identi,gtk_entry_get_text(GTK_ENTRY(iden)));
k=rechercher_election(identi);
if (k==0)
	{

	output=lookup_widget(button,"label2_SuppEl");
	gtk_label_set_text(GTK_LABEL(output), "ID INTROUVABLE");
	}
if (k==1)	
	{	

supprimer_election(identi);
windowElection=lookup_widget(button,"window_election");
tree=lookup_widget(windowElection,"treeview1_affElection");
afficher_election(tree);
output=lookup_widget(button,"label2_SuppEl");
gtk_label_set_text(GTK_LABEL(output), "Supprimer avec Succes");
}

}
void
on_button2_affElect_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *tree,*windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
windowElection=create_window_election();
tree=lookup_widget(windowElection,"treeview1_affElection");

afficher_election(tree);

gtk_widget_hide(windowElection);
gtk_widget_show(windowElection);

}




void
on_radiobutton1_nbr1_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "12");
}


void
on_radiobutton1_nbr2_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "16");
}


void
on_radiobutton1_nbr3_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "22");
}


void
on_radiobutton1_nbr4_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "30");
}


void
on_radiobutton1_nbr5_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "36");
}


void
on_radiobutton1_nbr7_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "40");
}


void
on_radiobutton1_nbr6_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output;
output=lookup_widget(button,"label1_nbrCons");
gtk_label_set_text(GTK_LABEL(output), "60");
}


void
on_treeview1_recElect_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button3_reche_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
remove("RechElect.txt");
char ident[20];
GtkWidget *id,*tree,*windowrechercher,*output;
int k;
windowrechercher=lookup_widget(button,"window_recherelect");
id = lookup_widget(button,"entry3_rechelect");
strcpy(ident,gtk_entry_get_text(GTK_ENTRY(id)));
k=rechercher_election(ident);
if (k==0)
	{

	output=lookup_widget(button,"label3_rechint");
	gtk_label_set_text(GTK_LABEL(output), "Election INTROUVABLE");
	}
if (k==1)	
	{	

tree=lookup_widget(windowrechercher,"treeview1_recElect");
afficher_rechercher_election(tree);
}

}


void
on_button3_retrecher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_rech, *menu_election;
window_rech=lookup_widget(button,"window_recherelect");
gtk_widget_destroy(window_rech);

menu_election=create_menu_election();
gtk_widget_show (menu_election);
}





void
on_button1_ModifierElection_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
election e1;
GtkWidget *windowajout, *windowelection,*id1,*jour1,*mois1,*annee1,*gou1,*munic1,*nbrh1,*nbrc1,*output2,*output3;
windowajout=create_window_ajouter_election();
windowelection=create_window_election();
id1 = lookup_widget(button,"entry1_ideclection");
gou1= lookup_widget(button,"entry1_gouvernorat");
jour1 = lookup_widget(button,"spinbutton1_jour");
mois1 = lookup_widget(button,"spinbutton1_mois");
annee1 = lookup_widget(button,"spinbutton1_annee");
munic1=lookup_widget(button,"comboboxentry1_munic");
strcpy(e1.identifiant,gtk_entry_get_text(GTK_ENTRY(id1)));
strcpy(e1.gouvernorat,gtk_entry_get_text(GTK_ENTRY(gou1)));
e1.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (jour1));
e1.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (mois1));
e1.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (annee1));
strcpy(e1.municipalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(munic1)));
if(x==1 )
{strcpy(e1.nbhabit,"5000");
e1.nbcons=12;
} 
else if(x==2)
{strcpy(e1.nbhabit,"5001->10000");
e1.nbcons=16;
}
else if(x==3)
{strcpy(e1.nbhabit,"10001->25000");
e1.nbcons=22;
}
else if(x==4)
{strcpy(e1.nbhabit,"25001->50000");
e1.nbcons=30;
}
else if(x==5)
{strcpy(e1.nbhabit,"50001->100000");
e1.nbcons=36;
}
else if(x==7)
{strcpy(e1.nbhabit,"100001->500000");
e1.nbcons=40;
}
else if(x==6)
{strcpy(e1.nbhabit,"Plus500000");
e1.nbcons=60;
}if(y==1){
if ((strcmp(e1.identifiant,"")==0)||( strcmp(e1.gouvernorat,"")==0)||( strcmp(e1.municipalite,"")==0)) {
output2=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output2), "Données manquantes. \n Veuillez remplir tout les champs!");
output3=lookup_widget(button,"label1_modifier");
gtk_label_set_text(GTK_LABEL(output3), "");
}
else
{
modifier_election(e1.identifiant,e1,"Election.txt");
output2=lookup_widget(button,"label2_donnemanq");
gtk_label_set_text(GTK_LABEL(output2), "");
output3=lookup_widget(button,"label1_modifier");
gtk_label_set_text(GTK_LABEL(output3), "Modifier avec Succes");
}}
x=0;
y=0;


}







void
on_button2_tachcalcul_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_calcul, *windowElection;
windowElection=lookup_widget(button,"window_election");
gtk_widget_destroy(windowElection);
window_calcul=create_window_calcul();
gtk_widget_show (window_calcul);
}


void
on_treeview4_TPHF_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button4_retCAl_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_calcul, *menu_election;
window_calcul=lookup_widget(button,"window_calcul");
gtk_widget_destroy(window_calcul);

menu_election=create_menu_election();
gtk_widget_show (menu_election);
}



void
on_button3_calculEl_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *output,*output1,*output2;
int tp;
int nbhomm,nbf;
output = lookup_widget(button, "label4_TPE") ;
tp=TPE("utilisateur.txt");
sprintf(Tpe,"%d",tp);
gtk_label_set_text(GTK_LABEL(output),Tpe);


output2 = lookup_widget(button, "label5_femme") ;
nbf=agemoyen("utilisateur.txt");
sprintf(Nbf,"%d",nbf);
gtk_label_set_text(GTK_LABEL(output2),Nbf);
}




void
on_toajout_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);
}


void
on_tomodif_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *window_ajouter_election, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
window_ajouter_election=create_window_ajouter_election ();
gtk_widget_show (window_ajouter_election);
}


void
on_tocherch_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowcherch, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowcherch=create_window_recherelect ();
gtk_widget_show (windowcherch);
}


void
on_tostat_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowstat, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowstat=create_window_calcul ();
gtk_widget_show (windowstat);
}


void
on_tosupp_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowelection, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowelection=create_window_election ();
gtk_widget_show (windowelection);
}


void
on_toaffich_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowelection, *menu_election;
menu_election=lookup_widget(button,"menu_election");
gtk_widget_destroy(menu_election);
windowelection=create_window_election ();
gtk_widget_show (windowelection);
}


void
on_buttretaffich_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *windowelection, *menu_election;
windowelection=lookup_widget(button,"windowelection");
gtk_widget_destroy(windowelection);

menu_election=create_menu_election();
gtk_widget_show (menu_election);
}

