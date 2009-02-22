///hell2o
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void button_clicked(GtkWidget *gw, gpointer data)
{  
  g_print ("Hello again - %s was pressed\n", (char *) data);
  //printf("BUTTON: %s", (char *)data);
}

void entry_print(GtkWidget *gw, GtkWidget *entry)
{  
  g_print ("%s\n", gtk_entry_get_text(entry));
  //printf("BUTTON: %s", (char *)data);
}

void entry_clear(GtkWidget *gw, GtkWidget *entry)
{ 
  gtk_entry_set_text(entry, "");
}


int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *tabs;
  GtkWidget *hbox;
  GtkWidget *hboxs[2];
  GtkWidget *tableBox[2];
  GtkWidget *button[2][2];
  GtkWidget *label[2];
  GtkWidget *input[2];
  GtkWidget *labelInput[2];
  GtkWidget *rightAlignment[2];
  GtkWidget *buttonBox;

  char *nameButton[2][2] = {
    { "Clear", "Print" },
    { "Button 2.1", "Button 2.2" }
  };
  char *nameLabel[2] = { "Label 1", "Label 2"};
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
    for(j=0; j<2; j++)  {
      button[i][j] = gtk_button_new_with_label(nameButton[i][j]);
      gtk_widget_set_size_request(button[i][j], 70, 35);
    }
    
    label[i] = gtk_label_new(nameLabel[i]);
  
  //initiating input label and entry
    labelInput[i] = gtk_label_new("Input here:");
    input[i] = gtk_entry_new();

    rightAlignment[i] = gtk_alignment_new(1, 0.5, 0.1, 0);
    gtk_container_add(GTK_CONTAINER(rightAlignment[i]), labelInput[i]);
    
    
    hboxs[i] = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hboxs[i]), rightAlignment[i], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hboxs[i]), input[i], FALSE, FALSE, 0);

    tableBox[i] = gtk_table_new(2, 2, FALSE);
    gtk_table_set_row_spacings(GTK_TABLE(tableBox[i]), 5);
    gtk_table_set_col_spacings(GTK_TABLE(tableBox[i]), 5);
    
  
    gtk_table_attach_defaults(GTK_TABLE(tableBox[0]), hboxs[i], 0+i, 1+i, 0, 1);
  }

  buttonBox = gtk_hbutton_box_new();
  gtk_box_pack_start(GTK_BOX(buttonBox), button[0][0], FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(buttonBox), button[0][1], FALSE, FALSE, 0);

  gtk_table_attach(GTK_TABLE(tableBox[0]), buttonBox, 1, 2, 1, 2, 0, 0, 0, 0);

  gtk_table_attach(GTK_TABLE(tableBox[1]), button[1][0], 1, 2, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0);
  
  //connecting buttons' callback to signal "clicked"
  g_signal_connect(G_OBJECT(button[1][0]), "clicked", 
      G_CALLBACK(button_clicked), (gpointer)"Button 2");

  for(i=0; i<2; i++)  { 
    g_signal_connect(G_OBJECT(button[0][1]), "clicked", 
        G_CALLBACK(entry_print), (gpointer)input[i]);
    g_signal_connect(G_OBJECT(button[0][0]), "clicked", 
      G_CALLBACK(entry_clear), (gpointer)input[i]);
  }
  
  g_signal_connect_swapped(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);


  //adding widgets to tabs
  gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tableBox[0], label[0]);
  gtk_container_set_border_width(GTK_CONTAINER(tableBox[0]), 5);
  printf("Button 1 added\n");
  gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tableBox[1], label[1]);
  printf("Button 2 added\n");
  
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
