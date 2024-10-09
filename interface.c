#include <gtk/gtk.h>

void on_submit(GtkWidget *widget, gpointer data) {
	const gchar *input1 = gtk_entry_get_text(GTK_ENTRY(data));
	g_print("Input1 : %s\n", input1);
}

int main(int argc, char *argv[]) {
	GtkWidget *Window;
	GtkWidget *grid;
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *button;

	gtk_init(&argc, &argv)

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Input Variables");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid layout
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create input boxes
    entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 0, 0, 1, 1);
    
    entry2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry2, 0, 1, 1, 1);
    
    // Create a submit button
    button = gtk_button_new_with_label("Submit");
    g_signal_connect(button, "clicked", G_CALLBACK(on_submit), entry1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the main loop
    gtk_main();

    return 0;
}



