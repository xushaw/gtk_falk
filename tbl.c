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

/*static void clr_callback( GtkWidget *widget, GtkWidget *entry )
{
    gtk_entry_set_text (GTK_ENTRY (entry), "");
}*/

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *notebook;
    GtkWidget *table;
    GtkWidget *menu, *menu_bar, *root_menu, *menu_items;
//    GtkWidget *x_hbox, *g_hbox, *vbox1, *vbox2, *bhbox;
    GtkWidget *vbox_main;
    GtkWidget *entry;
    GtkWidget *button_sch;// *button_clr;
    GtkWidget *label1, *label2;
    char buf[512];//?  1024 - segfault;
    int i;
    
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
    notebook = gtk_notebook_new ();
    table = gtk_table_new (3, 2, TRUE);
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
    gtk_box_pack_start (GTK_BOX (vbox_main), menu_bar, FALSE, FALSE, 2);
    gtk_widget_show (menu_bar);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);

    gtk_container_add (GTK_CONTAINER (window), vbox_main);
    gtk_container_add (GTK_CONTAINER (vbox_main), menu_bar);
    gtk_container_add (GTK_CONTAINER (vbox_main), notebook);
    gtk_container_add (GTK_CONTAINER (notebook), table);

   // button_clr = gtk_button_new_with_label ("Сброс");

  //  gtk_widget_set_size_request (button_clr, 100, 75);

    label1 = gtk_label_new ("Выбор силового преобразователя частоты");
    gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), table, label1);
    label2 = gtk_label_new ("МП");
    gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), table, label2, 2);

        button_sch = gtk_button_new_with_label ("Поиск"); 
        gtk_widget_set_size_request (button_sch, 100, 75);
        gtk_table_attach_defaults (GTK_TABLE (table), button_sch, 1, 2, 2, 3);
        gtk_widget_show (button_sch);
for (i=0; i<2; i++)
{    
    entry = gtk_entry_new ();
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 0, 1, 0+i, 1+i);
    g_signal_connect (G_OBJECT (button_sch), "clicked",
                      G_CALLBACK (sch_callback), (gpointer) entry);
    gtk_widget_show(entry);
}

for (i=0; i<1; i++)
{    
    entry = gtk_entry_new ();
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 0+i, 1+i);
    g_signal_connect (G_OBJECT (button_sch), "clicked",
                      G_CALLBACK (sch_callback), (gpointer) entry);
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