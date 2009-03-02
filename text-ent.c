#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

/*static void enter_callback( GtkWidget *widget,
                              GtkWidget *entry ) 
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}*/
//static void menuitem_response (gchar *);

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

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *x_hbox, *g_hbox, *vbox1, *vbox2, *bhbox, *vbox_main;
   // GtkWidget *entry1, *entry2, *entry3, *entry4, *entry5;
    GtkWidget *entry;
    GtkWidget *button_sch, *button_clr;
    GtkWidget *notebook;
    GtkWidget *label1, *label2;
 //   GtkWidget *frame1, *frame2, *frame3, *frame4, *frame5;
    GtkWidget *frame; 
/*    GtkWidget *menu;
    GtkWidget *menu_bar;
    GtkWidget *root_menu;
    GtkWidget *menu_items;*/
//    char buf[512];//?  1024 - segfault;
    char *frame_label_1[3] = {"Вх пар","Вых пар", "Реж корр"};
//    char frame_label_2[2] = {"Защитн ф-ции", "еще что-то"};
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
//-----------------------------------------------    
/*    menu = gtk_menu_new ();

    for (i=0; i<3; i++)
    {
        sprintf(buf, "Подменю-%d", i);
        menu_items = gtk_menu_item_new_with_label (buf);
        gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);//add menu-item to menu

        g_signal_connect_swapped (G_OBJECT (menu_items), "activate",
                                  G_CALLBACK (menuitem_response),  (gpointer) g_strdup (buf));
        gtk_widget_show (menu_items);
    }
    root_menu = gtk_menu_item_new_with_label ("Файл");
    gtk_widget_show (root_menu);

    gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);

    menu_bar = gtk_menu_bar_new ();
//    gtk_box_pack_start (GTK_BOX (vbox1), menu_bar, FALSE, FALSE, 2);//2?
    gtk_widget_show (menu_bar);

    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);*/

    x_hbox = gtk_hbox_new (FALSE, 0);
    g_hbox = gtk_hbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), notebook);
 //   gtk_container_add (GTK_CONTAINER (window), vbox_main);
 //   gtk_container_add (GTK_CONTAINER (vbox_main), menu_bar);
 //   gtk_container_add (GTK_CONTAINER (vbox_main), notebook);
    gtk_container_add (GTK_CONTAINER (notebook), x_hbox);

//    gtk_widget_set_size_request (button_sch, 100, 75);
//    gtk_widget_set_size_request (button_clr, 100, 75);

    label1 = gtk_label_new ("Выбор силового преобразователя частоты");
    gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), x_hbox, label1);
    label2 = gtk_label_new ("МП");
    gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), g_hbox, label2, 2);



//-----------------------
for (i=0; i<3; i++)
{
    entry = gtk_entry_new ();
    frame = gtk_frame_new (NULL);
    gtk_container_add (GTK_CONTAINER (frame), entry);
    gtk_container_add (GTK_CONTAINER (vbox1), frame);
    gtk_frame_set_label (GTK_FRAME (frame), (gpointer) frame_label_1[i]);
    g_signal_connect (G_OBJECT (button_sch), "clicked",
                      G_CALLBACK (sch_callback), (gpointer) entry);//???
    g_signal_connect (G_OBJECT (button_clr), "clicked",
                      G_CALLBACK (clr_callback), (gpointer) entry);
    gtk_frame_set_label_align (GTK_FRAME (frame), 0.5, 0.0);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);
    gtk_box_pack_start (GTK_BOX (vbox1), frame, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (frame), entry, TRUE, TRUE, 0);
    gtk_widget_show(entry);
    gtk_widget_show(frame);

}    
         button_sch = gtk_button_new_with_label ("Поиск"); 
         button_clr = gtk_button_new_with_label ("Сброс");

/*         g_signal_connect (G_OBJECT (button_sch), "clicked",
                           G_CALLBACK (sch_callback), (gpointer) entry1);

g_signal_connect (G_OBJECT (button_sch), "clicked",
                           G_CALLBACK (sch_callback), (gpointer) entry2);
g_signal_connect (G_OBJECT (button_sch), "clicked",
                           G_CALLBACK (sch_callback), (gpointer) entry3);
g_signal_connect (G_OBJECT (button_sch), "clicked",
                           G_CALLBACK (sch_callback), (gpointer) entry4);
g_signal_connect (G_OBJECT (button_sch), "clicked",
                           G_CALLBACK (sch_callback), (gpointer) entry5);*/

/*g_signal_connect (G_OBJECT (button_clr), "clicked",
                           G_CALLBACK (clr_callback), (gpointer) entry1);
g_signal_connect (G_OBJECT (button_clr), "clicked",
                           G_CALLBACK (clr_callback), (gpointer) entry2);
g_signal_connect (G_OBJECT (button_clr), "clicked",
                           G_CALLBACK (clr_callback), (gpointer) entry3);
g_signal_connect (G_OBJECT (button_clr), "clicked",
                           G_CALLBACK (clr_callback), (gpointer) entry4);
g_signal_connect (G_OBJECT (button_clr), "clicked",
                           G_CALLBACK (clr_callback), (gpointer) entry5);*/

  /*       vbox1 = gtk_vbox_new (TRUE, 0); //выравнивание кнопочек
         vbox2 = gtk_vbox_new (TRUE, 0); //то же
         bhbox = gtk_hbox_new (FALSE, 0);*/

/*         frame1 = gtk_frame_new (NULL);
         frame2 = gtk_frame_new (NULL);
         frame3 = gtk_frame_new (NULL);
         frame4 = gtk_frame_new (NULL);
         frame5 = gtk_frame_new (NULL);*/

    gtk_container_add (GTK_CONTAINER (x_hbox), vbox1);
    
//    gtk_box_pack_start (GTK_BOX (vbox_main), menu_bar, TRUE, TRUE, 0);//2? vbox1

    gtk_container_add (GTK_CONTAINER (x_hbox), vbox2);
//    gtk_container_add (GTK_CONTAINER (g_hbox), vbox2);
/*    gtk_container_add (GTK_CONTAINER (vbox1), frame1);
    gtk_container_add (GTK_CONTAINER (vbox1), frame2);

    gtk_container_add (GTK_CONTAINER (vbox2), frame3);
    gtk_container_add (GTK_CONTAINER (vbox2), frame4); 

    gtk_container_add (GTK_CONTAINER (vbox1), frame5); */

/*    gtk_frame_set_label (GTK_FRAME (frame1), "Входные параметры");
    gtk_frame_set_label (GTK_FRAME (frame2), "Выходные параметры");
    gtk_frame_set_label (GTK_FRAME (frame3), "Рабочие функции");
    gtk_frame_set_label (GTK_FRAME (frame4), "Защитные функции");
    gtk_frame_set_label (GTK_FRAME (frame5), "Режимы коррекции");*/
 /*   gtk_frame_set_label_align (GTK_FRAME (frame1), 0.5, 0.0);//1.0 0.0
    gtk_frame_set_label_align (GTK_FRAME (frame2), 0.5, 0.0);// comment it!
    gtk_frame_set_label_align (GTK_FRAME (frame3), 0.5, 0.0);
    gtk_frame_set_label_align (GTK_FRAME (frame4), 0.5, 0.0);
    gtk_frame_set_label_align (GTK_FRAME (frame5), 0.5, 0.0);*/
/*    gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_ETCHED_OUT);
    gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_ETCHED_OUT);
    gtk_frame_set_shadow_type (GTK_FRAME (frame3), GTK_SHADOW_ETCHED_OUT);
    gtk_frame_set_shadow_type (GTK_FRAME (frame4), GTK_SHADOW_ETCHED_OUT);
    gtk_frame_set_shadow_type (GTK_FRAME (frame5), GTK_SHADOW_ETCHED_OUT);*/

/*    gtk_container_add (GTK_CONTAINER (frame1), entry1);
    gtk_container_add (GTK_CONTAINER (frame2), entry2);
    gtk_container_add (GTK_CONTAINER (frame3), entry3);
    gtk_container_add (GTK_CONTAINER (frame4), entry4);
    gtk_container_add (GTK_CONTAINER (frame5), entry5);*/

    gtk_container_add (GTK_CONTAINER (vbox2), bhbox);
    gtk_container_add (GTK_CONTAINER (bhbox), button_sch);
    gtk_container_add (GTK_CONTAINER (bhbox), button_clr);
//    gtk_container_add (GTK_CONTAINER (align), entry3);
//    gtk_container_add (GTK_CONTAINER (align), entry4);
//    gtk_container_add (GTK_CONTAINER (align), button_sch); 
//    align = gtk_alignment_new (10, 10, 20, 20);
//    gtk_widget_show (align);
    gtk_box_pack_start (GTK_BOX (x_hbox),  vbox1, TRUE, TRUE, 0); 
    gtk_box_pack_start (GTK_BOX (x_hbox),  vbox2, TRUE, TRUE, 0); 
    gtk_box_pack_start (GTK_BOX (g_hbox),  vbox2, TRUE, TRUE, 0); 
/*    gtk_box_pack_start (GTK_BOX (vbox1), entry1, TRUE, TRUE, 0); 
    gtk_box_pack_start (GTK_BOX (vbox1), entry2, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox2), entry3, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox2), entry4, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox1), entry5, TRUE, TRUE, 0);*/
    gtk_box_pack_start (GTK_BOX (vbox2), button_sch, TRUE, TRUE, 0);
/*    gtk_widget_show (entry1);
    gtk_widget_show (entry2);
    gtk_widget_show (entry3);
    gtk_widget_show (entry4);
    gtk_widget_show (entry5);*/
    gtk_widget_show (button_sch);
    gtk_widget_show (button_clr);
/*    gtk_widget_show (frame1);
    gtk_widget_show (frame2);
    gtk_widget_show (frame3);
    gtk_widget_show (frame4);
    gtk_widget_show (frame5);*/
    gtk_widget_show (bhbox);
    gtk_widget_show (vbox1);
    gtk_widget_show (vbox2);
    gtk_widget_show (x_hbox);
    gtk_widget_show (g_hbox);
    gtk_widget_show (notebook); 
//    gtk_widget_show (vbox_main); 
    gtk_widget_show (window);

    gtk_main();

    return 0;
}

/*static void menuitem_response( gchar *string )
{
        printf ("%s\n", string);
}*/
