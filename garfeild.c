///hell2o
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void entry_print(GtkWidget *gw, GtkWidget *entry)
{  
  g_print ("%s\n", gtk_entry_get_text(GTK_ENTRY(entry)));
  //printf("BUTTON: %s", (char *)data);
}

void entry_clear(GtkWidget *gw, GtkWidget *entry)
{ 
  gtk_entry_set_text(GTK_ENTRY(entry), "");
}

void entry_enter(GtkWidget *gw, GtkWidget *button)
{
  g_signal_emit_by_name(G_OBJECT(button), "clicked");
}

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *tabs;
  GtkWidget *hbox;
  GtkWidget *hboxs[2][2];
  GtkWidget *tableBox[2];
  GtkWidget *button[2][2];
  GtkWidget *label[2];
  GtkWidget *input[2][2];
  GtkWidget *labelInput[2][2];
  GtkWidget *rightAlignment[2][2];
  GtkWidget *buttonBox[2];

  char *nameButton[2] = { "Clear", "Print" };
  char *nameLabel[2] = { "Label 1", "Label 2"};
  char *nameInput[2][2] = {
    { "Input 1.1", "Input 1.2" },
    { "Input 2.1", "Input 2.2" }
  };
  int i=0;
  int j=0;

  //initiating gtk
  gtk_init(&argc, &argv);

  //initiating window, hbox and tabs
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  hbox = gtk_hbox_new(TRUE, 10);
  tabs = gtk_notebook_new();

  //initiating buttons and labels
  for(i=0; i<2; i++)  {
    label[i] = gtk_label_new(nameLabel[i]);
    buttonBox[i] = gtk_hbutton_box_new();
    tableBox[i] = gtk_table_new(2, 2, FALSE);
  
    for(j=0; j<2; j++)  {
      button[i][j] = gtk_button_new_with_label(nameButton[j]);
      gtk_widget_set_size_request(button[i][j], 70, 35);
    
      //initiating input label and entry
      labelInput[i][j] = gtk_label_new(nameInput[i][j]);
      input[i][j] = gtk_entry_new();
      
      rightAlignment[i][j] = gtk_alignment_new(1, 0.5, 0.1, 0);
      
      hboxs[i][j] = gtk_hbox_new(FALSE, 5);
      
      gtk_container_add(GTK_CONTAINER(rightAlignment[i][j]), labelInput[i][j]);
      
      gtk_box_pack_start(GTK_BOX(hboxs[i][j]), rightAlignment[i][j], FALSE, FALSE, 0);
      gtk_box_pack_start(GTK_BOX(hboxs[i][j]), input[i][j], FALSE, FALSE, 0);
    }

    gtk_table_set_row_spacings(GTK_TABLE(tableBox[i]), 5);
    gtk_table_set_col_spacings(GTK_TABLE(tableBox[i]), 5);
    
  
    for(j=0; j<2; j++)
      gtk_table_attach_defaults(GTK_TABLE(tableBox[i]), hboxs[i][j], 0+j, 1+j, 0, 1);
  
    for(j=0; j<2; j++)
      gtk_box_pack_start(GTK_BOX(buttonBox[i]), button[i][j], FALSE, FALSE, 0);
  }


  gtk_table_attach(GTK_TABLE(tableBox[0]), buttonBox[0], 1, 2, 1, 2, GTK_EXPAND, GTK_EXPAND, 1, 0);

  gtk_table_attach(GTK_TABLE(tableBox[1]), buttonBox[1], 1, 2, 1, 2, GTK_EXPAND, GTK_EXPAND, 1, 0);
  
  //connecting buttons' callback to signal "clicked"
  for(i=0; i<2; i++)  {
    for(j=0; j<2; j++)  {
      g_signal_connect(G_OBJECT(button[i][0]), "clicked", 
          G_CALLBACK(entry_clear), (gpointer) input[i][j]);

      g_signal_connect(G_OBJECT(button[i][1]), "clicked", 
          G_CALLBACK(entry_print), (gpointer) input[i][j]);
      
      g_signal_connect(G_OBJECT(input[i][j]), "activate",
          G_CALLBACK(entry_enter), (gpointer) button[i][1]);
    }
  }
  
  g_signal_connect_swapped(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);


  //adding widgets to tabs
  for(i=0; i<2; i++)
  {
    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tableBox[i], label[i]);
    gtk_container_set_border_width(GTK_CONTAINER(tableBox[i]), 5);
  }
  
  //let's show them all
  gtk_widget_show(tabs);

  gtk_container_add(GTK_CONTAINER(hbox), tabs);
  gtk_widget_show(hbox);
  
  gtk_container_add(GTK_CONTAINER(window), hbox);
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);
  gtk_widget_show_all(window);
  
  //let's run main loop
  gtk_main(); 

  return 0;
}
