#include <gtk/gtk.h>
#include <stdio.h>

typedef struct
{
    GObject *entry;
    char num;
}InpData;


void num_button_handler(GtkWidget *widget, gpointer data)
{
    InpData *inp_data = data;
    GtkEntry *entry = GTK_ENTRY(inp_data->entry);

    //select the text in the entry append the new one and set that one as the new text
    const gchar *text = gtk_entry_get_text(entry);
    gchar *new_text = g_strconcat(text, &(inp_data->num), NULL);
    gtk_entry_set_text(entry, new_text);
}

void compute(GtkWidget *widget, gpointer data)
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
    g_signal_connect(button, "clicked", G_CALLBACK(compute), NULL);
    /*
    InpData data = 
    {
        .entry=entry,
        .num='1'
    };
    button = gtk_builder_get_object(builder, "button_1");
    g_signal_connect(button, "clicked", G_CALLBACK(num_button_handler), &data);

    data.num = '2';
    button = gtk_builder_get_object(builder, "button_2");
    g_signal_connect(button, "clicked", G_CALLBACK(num_button_handler), &data);
    */
    char buffer[9];

    for (char i = '0'; i <= '9'; i++) 
    {
        //instantiate new struct data handled by gtk
        InpData *data = g_new(InpData, 1);
        data->entry = entry;
        data->num = i;

        sprintf(buffer, "button_%c", i);
        button = gtk_builder_get_object(builder, buffer);
        g_signal_connect(button, "clicked", G_CALLBACK(num_button_handler), data);
    }

    gtk_main();


    return 0;
}