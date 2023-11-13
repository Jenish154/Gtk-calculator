#include <gtk/gtk.h>

typedef struct
{
    GObject *entry;
    int num;
}InpData;


void calculate(GtkWidget *widget, gpointer data)
{

}

int main(int argc, char **argv)
{
    GtkBuilder *builder;
    GObject *window, *button, *entry, *label;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "calculator.ui", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);

        return 1;
    }

    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    entry = gtk_builder_get_object(builder, "inp");
    
    button = gtk_builder_get_object(builder, "button_calc");
    g_signal_connect(button, "clicked", G_CALLBACK(calculate), NULL);

    button = gtk_builder_get_object(builder, "button_1");

    gtk_main();


    return 0;
}