#include <gtk/gtk.h>
#include <stdio.h>

const char *app_id = "org.manulasker.gtk4Learning";
int wrap_state = 1;

static void
wrap_text(GtkButton *btn, GtkTextView *text_view){
    if (wrap_state){
        gtk_text_view_set_wrap_mode(text_view, GTK_WRAP_WORD_CHAR);
        wrap_state = 0;
    }else{
        gtk_text_view_set_wrap_mode(text_view, GTK_WRAP_NONE);
        wrap_state = 1;
    }
}

static void
activate_handler(GApplication *app, gpointer *user_data){
    GtkWidget *win;
    GtkWidget *s_win;
    GtkWidget *text_view;
    GtkWidget *wrap_btn;
    GtkWidget *box;
    GtkTextBuffer *text_buffer;

    gchar *text;

    text =
        "Once upon a time, there was an old man who was called Taketori-no-Okina. "
        "It is a japanese word that means a man whose work is making bamboo baskets.\n"
        "One day, he went into a hill and found a shining bamboo. "
        "\"What a mysterious bamboo it is!,\" he said. "
        "He cut it, then there was a small cute baby girl in it. "
        "The girl was shining faintly. "
        "He thought this baby girl is a gift from Heaven and took her home.\n"
        "His wife was surprized at his story. "
        "They were very happy because they had no children. "
        ;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "taketori");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    s_win = gtk_scrolled_window_new();

    gtk_box_append(GTK_BOX(box), s_win);

    text_view = gtk_text_view_new();
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(text_buffer, text, -1);

    wrap_btn = gtk_button_new_with_label("wrap text");
    gtk_box_append(GTK_BOX(box), wrap_btn);
    g_signal_connect(wrap_btn, "clicked", G_CALLBACK(wrap_text), GTK_TEXT_VIEW(text_view));

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(s_win), text_view);
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(s_win), 300);

    gtk_window_set_child(GTK_WINDOW(win), box);
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
