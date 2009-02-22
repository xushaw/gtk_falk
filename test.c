#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void button_callback(GtkWidget *widget, gpointer data)
{
  g_print("Button %s\n", (gchar *) data);
}

int main(int argc, char *argv[])
{
  GtkWidget *button;
  GtkWidget *table;
  GtkWidget *window;
  char *label[2] = {"1", "2"};
  int i;

  gtk_init(&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  table = gtk_table_new(2, 1, FALSE);
  
  gtk_container_add (GTK_CONTAINER (window), table);
  
  for(i=0; i<2; i++)
  {
    button = gtk_button_new_with_label(label[i]);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0+i, 1+i, 0, 1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(button_callback), (gpointer) label[i]);
    gtk_widget_show(button);
  }

  //gtk_widget_show(table);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
