#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include "expressionEvaluator.h"

typedef struct
{
    GObject *entry;
    char num;
}InpData;

const char operators[] = {'+', '-', '*', '/'};

int char_is_op(char new_char)
{
    for (int i=0; i<(sizeof(operators)/sizeof(char)); i++)
    {
        if (new_char == operators[i])
            return 1;
    }

    return 0;
}

int validate_entry(const gchar *ent_text, char new_char, int length)
{
    if (length == 0) 
    {
        if (char_is_op(new_char))
            return 0;
    } else
    {
        if(char_is_op(new_char) && char_is_op(ent_text[length-1]))
            return 0;
    }
    return 1;
}


void num_button_handler(GtkWidget *widget, gpointer data)
{
    InpData *inp_data = data;
    GtkEntry *entry = GTK_ENTRY(inp_data->entry);

    //get text and length of text from entry
    const gchar *text_from_entry = gtk_entry_get_text(entry);
    size_t leng = gtk_entry_get_text_length(entry);


    //check whether the entered char will result in a valid arithmetic expression
    if (validate_entry(text_from_entry, inp_data->num, leng))
    {
        //select the text in the entry append the new one and set that one as the new text
        //const gchar *text = gtk_entry_get_text(entry);
        //gchar *new_text = g_strconcat(text, &(inp_data->num), NULL);
        gchar *new_text = g_strdup_printf("%s%c", gtk_entry_get_text(entry), inp_data->num);
        gtk_entry_set_text(entry, new_text);

        g_free(new_text);

    }
    
    
}

void compute(GtkWidget *widget, gpointer data)
{
    InpData *inp_data = data;
    GtkEntry *entry = GTK_ENTRY(inp_data->entry);

    //get the expression
    const gchar *text_from_entry = gtk_entry_get_text(entry);
    bool success;
    double result = calculate(text_from_entry, &success);

    gchar *result_string;

    //if number has no fractional part use integer
    if (result == (int)result) 
    {
        result_string = g_strdup_printf("%d", (int)result);
    } else
    {
        result_string = g_strdup_printf("%lf", result);
    }
    gtk_entry_set_text(entry, result_string);

    //free the memory
    g_free(result_string);
}

int main(int argc, char **argv)
{
    GtkBuilder *builder;
    GObject *window, *button, *entry, *label;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "src/calculator.ui", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);

        return 1;
    }

    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    entry = gtk_builder_get_object(builder, "inp");

    InpData *data = g_new(InpData, 1);
    data->entry = entry;
    
    button = gtk_builder_get_object(builder, "button_calc");
    g_signal_connect(button, "clicked", G_CALLBACK(compute), data);
    
    char buffer[9];
    InpData *struct_arr[14] = {data};

    for (char i = '0'; i <= '9'; i++) 
    {
        //instantiate new struct data handled by gtk
        data = g_new(InpData, 1);
        data->entry = entry;
        data->num = i;

        sprintf(buffer, "button_%c", i);
        button = gtk_builder_get_object(builder, buffer);
        g_signal_connect(button, "clicked", G_CALLBACK(num_button_handler), data);
        struct_arr[i+1] = data;
    }

    for (int j = 0; j<(sizeof(operators)/sizeof(char)); j++)
    {
        data = g_new(InpData, 1);
        data->entry = entry;
        data->num = operators[j];

        sprintf(buffer, "button_%c", operators[j]);
        button = gtk_builder_get_object(builder, buffer);
        g_signal_connect(button, "clicked", G_CALLBACK(num_button_handler), data);
        struct_arr[j+11] = data;
    }

    gtk_main();
    for (int ind = 0; ind <=13; ind++)
    {
        g_free(struct_arr[ind]);
    }

    return 0;
}