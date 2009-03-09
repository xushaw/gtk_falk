#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "table.h"

static void
tree_selection_changed_cb (GtkTreeSelection *selection, gpointer data)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *author;
    gboolean flag=FALSE;

    if (gtk_tree_selection_get_selected (selection, &model, &iter))
    {
        gtk_tree_model_get (model, &iter, AUTHOR_COLUMN, &author, -1);
        gtk_tree_model_get (model, &iter, CHECKED_COLUMN, &flag, -1);
        
        if ( flag == FALSE)
        {
            gtk_tree_store_set (GTK_TREE_STORE(model), &iter,
                    CHECKED_COLUMN, TRUE,
                    -1);
            g_print ("You selected a book by %s\n", author);

            g_free (author);
        }
        else if ( flag == TRUE)
        {
            gtk_tree_store_set (GTK_TREE_STORE(model), &iter,
                    CHECKED_COLUMN, FALSE,
                    -1);
        }
    }
}

void button_callback(GtkWidget *widget, gpointer data)
{
  g_print("Button %s\n", (gchar *) data);
}
 
int main(int argc, char *argv[])
{
  GtkWidget *button;
  GtkWidget *table;
  GtkWidget *window;
  GtkWidget *tree;
  GtkTreeStore *store;

  const char *label[2] = {"1", "2"};
  const char *names[3] = { "O123131ne", "Two", "HELLO"};
  const char *labelColumn[N_COLUMNS] = { "Author", "Title", "Checked out" };
  int i;
 
  gtk_init(&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 
  table = gtk_table_new(2, 2, FALSE);
  
  gtk_container_add (GTK_CONTAINER (window), table);
  
  for(i=0; i<2; i++)
  {
    button = gtk_button_new_with_label(label[i]);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0+i, 1+i, 0, 1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(button_callback), (gpointer) label[i]);
    gtk_widget_show(button);
  }

  store = gtk_tree_store_new (N_COLUMNS,
          G_TYPE_STRING,
          G_TYPE_STRING,
          G_TYPE_BOOLEAN);

  tree = setup_table(store, labelColumn);
  
  set_table_info(store, names, FALSE);


  gtk_table_attach_defaults(GTK_TABLE(table), tree, 0, 2, 1, 2);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
          G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
 
