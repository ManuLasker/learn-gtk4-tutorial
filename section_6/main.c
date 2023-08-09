#include <gtk/gtk.h>
#include <stdio.h>

const char *app_id = "org.manulasker.gtk4Learning";

static void
click1_cb(GtkButton *btn){
    const char* button_label;
    button_label = gtk_button_get_label(btn);

    if (g_strcmp0("Hello", button_label) == 0)
        gtk_button_set_label(btn, "Bye");
    else
        gtk_button_set_label(btn, "Hello");

}

static void
click2_cb(GtkButton *btn, GtkWindow *win){
    g_print("Bye World Clicked\n");
    gtk_window_destroy(win);
}

static void
activate_handler(GApplication *app, gpointer *user_data){
    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *lab, *button_1, *button_2;

    win = gtk_application_window_new(GTK_APPLICATION(app));

    gtk_window_set_title(GTK_WINDOW(win), "test window");
    gtk_window_set_default_size(GTK_WINDOW(win), 500, 600);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 200);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
    gtk_window_set_child(GTK_WINDOW(win), box);

    lab = gtk_label_new("Hello World!");
    gtk_box_append(GTK_BOX(box), lab);

    button_1 = gtk_button_new_with_label("Hello World Button!");
    gtk_box_insert_child_after(GTK_BOX(box), button_1, lab);
    g_signal_connect(button_1, "clicked", G_CALLBACK(click1_cb), NULL);

    button_2 = gtk_button_new_with_label("Bye World Button!");
    gtk_box_insert_child_after(GTK_BOX(box), button_2, button_1);
    g_signal_connect(button_2, "clicked", G_CALLBACK(click2_cb), win);


    gtk_window_present(GTK_WINDOW(win));
}

int
main (int argc, char **argv){
    GtkApplication *app;
    int stat;

    app = gtk_application_new(app_id, G_APPLICATION_FLAGS_NONE); // create an app
    g_signal_connect(app, "activate", G_CALLBACK(activate_handler), NULL); // connect activate signal
    stat = g_application_run(G_APPLICATION(app), argc, argv); // run the app

    g_object_unref(app); // unref the app

    return stat;
}
