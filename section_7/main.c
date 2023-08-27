#include <gtk/gtk.h>
#include <stdio.h>

const char *app_id = "org.manulasker.gtk4Learning";

static void
app_activate(GApplication *app){
    g_printerr("Error no files passed through command line arguments!");
}

static void
app_open(GApplication *app, GFile **files, int n_files, char *hint){
    g_print("Command line arguments provided!");
    GtkWidget *win, *nb, *scr, *tv, *lab;
    GtkNotebookPage *nbp;
    GtkTextBuffer *tb;
    char *contents, *filename;
    gsize length;
    GError *err = NULL;

    // create window and register to app
    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_default_size(GTK_WINDOW(win), 500, 500);

    nb = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(win), nb);
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(nb), TRUE);



    for (int i = 0; i < n_files; i++) {
        if (g_file_load_contents(files[i], NULL, &contents, &length, NULL, &err)) {

            tv = gtk_text_view_new();
            tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
            scr = gtk_scrolled_window_new();
            gtk_text_view_set_editable(GTK_TEXT_VIEW(tv), FALSE);
            gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);
            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), tv);

            gtk_text_buffer_set_text(GTK_TEXT_BUFFER(tb), contents, length);
            g_free(contents);

            if ((filename = g_file_get_basename (files[i])) != NULL) {
                lab = gtk_label_new (filename);
                g_free (filename);
            } else
                lab = gtk_label_new ("");

            gtk_notebook_append_page (GTK_NOTEBOOK (nb), scr, lab);
            nbp = gtk_notebook_get_page (GTK_NOTEBOOK (nb), scr);
            g_object_set (nbp, "tab-expand", TRUE, NULL);

        } else {
            g_printerr ("File can't be open %s.\n", err->message);
            g_clear_error (&err);
        }
    }

    if (gtk_notebook_get_n_pages (GTK_NOTEBOOK (nb)) > 0){
        gtk_window_present (GTK_WINDOW(win));
    } else {
        gtk_window_destroy (GTK_WINDOW(win));
    }
}

int
main (int argc, char **argv){
    GtkApplication *app;
    int stat;

    app = gtk_application_new(app_id, G_APPLICATION_HANDLES_OPEN); // create an app
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL); // Handles the activate signal when no command line arguments are passed
    g_signal_connect(app, "open", G_CALLBACK(app_open), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv); // run the app
    g_object_unref(app); // unref the app
    return stat;
}
