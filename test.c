#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

enum
{
    TITLE_COLUMN,
    AUTHOR_COLUMN,
    CHECKED_COLUMN,
    N_COLUMNS
};

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

void set_column(GtkWidget *tree, char *labelColumn[])
{
  GtkTreeViewColumn *column;
  GtkCellRenderer *renderer;
  int i;

  for ( i=0; i < N_COLUMNS; i++ )
  {

      if ( i == 2 )
      {
          renderer = gtk_cell_renderer_toggle_new ();
          column = gtk_tree_view_column_new_with_attributes (labelColumn[i], renderer,
                  "active", i,
                  NULL);
      }
      else
      {
          renderer = gtk_cell_renderer_text_new ();
          column = gtk_tree_view_column_new_with_attributes (labelColumn[i], renderer,
                  "text", i,
                  NULL);
      }

      gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
  }
}

void set_table_info(GtkTreeStore *store, char *names[], gboolean flag)
{
    GtkTreeIter   iter;

    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter,
            TITLE_COLUMN, names[TITLE_COLUMN],
            AUTHOR_COLUMN, names[AUTHOR_COLUMN],
            CHECKED_COLUMN, flag,
            -1);
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
  GtkTreeStore *store;
  GtkWidget *tree;

  char *label[2] = {"1", "2"};
  char *names[3] = { "One", "Two"};
  char *labelColumn[N_COLUMNS] = { "Author", "Title", "Checked out" };
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

  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));

  g_object_unref (G_OBJECT (store));

  set_column(tree, labelColumn);

  set_table_info(store, names, FALSE);

  gtk_table_attach_defaults(GTK_TABLE(table), tree, 0, 2, 1, 2);

  GtkTreeSelection *select;

  select = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree));
  gtk_tree_selection_set_mode (select, GTK_SELECTION_SINGLE);
  g_signal_connect (G_OBJECT (select), "changed",
          G_CALLBACK (tree_selection_changed_cb),
          NULL);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
          G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
 
