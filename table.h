#ifndef TABLE_H
#define TABLE_H

enum
{
    TITLE_COLUMN,
    AUTHOR_COLUMN,
    CHECKED_COLUMN,
    N_COLUMNS
};

void set_column(GtkWidget *tree, char *labelColumn[]);

void set_table_info(GtkTreeStore *store,const char *names[], gboolean flag);

GtkWidget* setup_table(GtkTreeStore *store, const char *labelColumn[]);

#endif   /* ----- #ifndef TABLE_INC  ----- */

