#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void button_clicked(GtkWidget *gw, gpointer data)
{  
  g_print ("Hello again - %s was pressed\n", (char *) data);
  //printf("BUTTON: %s", (char *)data);
}


int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *tabs;
  GtkWidget *hbox;
  GtkWidget *button[2];
  GtkWidget *label[2];

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  hbox = gtk_hbox_new(TRUE, 10);
  
  tabs = gtk_notebook_new();

  button[0] = gtk_button_new_with_label("Button 1");
  label[0] = gtk_label_new("Label 1");
  
  button[1] = gtk_button_new_with_label("Button 2");
  label[1] = gtk_label_new("Label 2");
  
  g_signal_connect(G_OBJECT(button[0]), "clicked", 
            G_CALLBACK(button_clicked), (gpointer)"Button 1");

  g_signal_connect(G_OBJECT(button[1]), "clicked", 
            G_CALLBACK(button_clicked), (gpointer)"Button 2");

  gtk_notebook_append_page(GTK_NOTEBOOK(tabs), button[0], label[0]);
  printf("Button 1 added\n");
  
  gtk_notebook_append_page(GTK_NOTEBOOK(tabs), button[1], label[1]);
  printf("Button 2 added\n");
  
  gtk_widget_show(tabs);
  gtk_container_add(GTK_CONTAINER(hbox), tabs);
  gtk_widget_show(hbox);
  
  gtk_container_add(GTK_CONTAINER(window), hbox);
  gtk_widget_show_all(window);
  
  gtk_main(); 

  return 0;
}
