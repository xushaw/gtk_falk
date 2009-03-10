#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void menuitem_response (gchar *);

static void sch_callback( GtkWidget *widget, GtkWidget *entry ) //1-й арг - кто отсылает сигнал
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
    g_print("    %s\n", entry_text);
}

static void clr_callback( GtkWidget *widget, GtkWidget *entry )
{
    gtk_entry_set_text (GTK_ENTRY (entry), "");
}

static void rand_callback (GtkWidget *widget, gpointer data)//gpointer data
{
//    g_print("Муррр!\n");
    short n;
    n=rand();
    if (n>10000)
        g_print("Мяф...\n");
    else if (n>5000)
        g_print("Миу..\n");
    else     
    g_print("Муррр!\n");
}

    

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *notebook;
    GtkWidget *table, *table2;
    GtkWidget *menu, *menu_bar, *root_menu, *menu_items;
    GtkWidget *vbox_main, *vbox;
    GtkWidget *entry;
    GtkWidget *button_sch, *button_clr;
    GtkWidget *label1, *label2;
    GtkWidget *cat_button;
    char buf[512];//?  1024 - segfault;
    int i,j;
    
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 500, 200); //500 150
    gtk_window_set_title (GTK_WINDOW (window), "выбор");
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (G_OBJECT (window), "delete_event",
                              G_CALLBACK (gtk_widget_destroy), 
                              G_OBJECT (window));

    vbox_main = gtk_vbox_new (FALSE, 0);
    vbox = gtk_vbox_new (TRUE, 0);
    notebook = gtk_notebook_new ();
    table = gtk_table_new (4, 2, TRUE);
    table2 = gtk_table_new (3, 3, TRUE);
    menu = gtk_menu_new ();

    for (i=0; i<3; i++)
    {
        sprintf(buf, "Подменю-%d", i);
        menu_items = gtk_menu_item_new_with_label (buf);
        gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);

        g_signal_connect_swapped (G_OBJECT (menu_items), "activate",
                                  G_CALLBACK (menuitem_response),  (gpointer) g_strdup (buf));
        gtk_widget_show (menu_items);
    }
    root_menu = gtk_menu_item_new_with_label ("Файл");
    gtk_widget_show (root_menu);
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
    menu_bar = gtk_menu_bar_new ();
    gtk_box_pack_start (GTK_BOX (vbox_main), menu_bar, FALSE, FALSE, 2);//same
    gtk_widget_show (menu_bar);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);

    cat_button = gtk_button_new_with_label ("(=^_^=)");
    gtk_table_attach_defaults (GTK_TABLE (table2), cat_button, 1, 2, 1, 2);

    gtk_container_add (GTK_CONTAINER (window), vbox_main);
    gtk_container_add (GTK_CONTAINER (vbox_main), notebook);
    gtk_container_add (GTK_CONTAINER (notebook), table);
    gtk_container_add (GTK_CONTAINER (vbox), table2);

    label1 = gtk_label_new ("Выбор силового преобразователя частоты");
    gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), table, label1);
    label2 = gtk_label_new ("МП");
    gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), vbox, label2, 2);
//    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), vbox, label2);//it works too!

        button_sch = gtk_button_new_with_label ("Поиск"); 
        gtk_widget_set_size_request (button_sch, 100, 75);
        gtk_table_attach_defaults (GTK_TABLE (table), button_sch, 0, 1, 3, 4);

        button_clr = gtk_button_new_with_label ("Сброс");
        gtk_widget_set_size_request (button_clr, 100, 75);
        gtk_table_attach_defaults (GTK_TABLE (table), button_clr, 1, 2, 3, 4);

        g_signal_connect (G_OBJECT (cat_button), "clicked",
                          G_CALLBACK (rand_callback), NULL);
 /*       g_signal_connect_swapped (G_OBJECT (cat_button), "clicked",
                                  G_CALLBACK (gtk_widget_destroy), G_OBJECT (notebook));*/

for (i=0; i<2; i++)
for (j=0; j<3; j++)
{    
    entry = gtk_entry_new ();
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 0+i, 1+i, 0+j, 1+j);
    g_signal_connect (G_OBJECT (button_sch), "clicked",
                      G_CALLBACK (sch_callback), (gpointer) entry); 
    g_signal_connect (G_OBJECT (button_clr), "clicked",
                      G_CALLBACK (clr_callback), (gpointer) entry);

    gtk_widget_show(entry);
}

 gtk_widget_show_all (window);

 gtk_main();
return 0;
}

static void menuitem_response( gchar *string )
{
        printf ("%s\n", string);
}
