#include "table.h"
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

void set_column(GtkWidget *tree, const char *labelColumn[])
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

void set_table_info(GtkTreeStore *store, const char *names[], gboolean flag)
{
    GtkTreeIter   iter;

    gtk_tree_store_append (store, &iter, NULL);  /* Acquire an iterator */
    gtk_tree_store_set (store, &iter,
            TITLE_COLUMN, names[TITLE_COLUMN],
            AUTHOR_COLUMN, names[AUTHOR_COLUMN],
            CHECKED_COLUMN, flag,
            -1);
}

GtkWidget* setup_table(GtkTreeStore *store, const char *labelColumn[])
{
  GtkWidget *tree;

  tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));

  set_column(tree, labelColumn);

  g_object_unref (G_OBJECT (store));

  g_print("setup\n");
  return tree;

}
