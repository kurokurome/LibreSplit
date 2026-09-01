#include "split_layout_dialog.h"
#include "component/components.h"
#include "src/logging.h"

#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdio.h>

static GtkWidget* split_layout_menu_singleton = NULL;

static void on_split_layout_menu_window_destroy(GtkWidget* widget, gpointer user_data)
{
    LOG_DEBUG("Destroying Split Layout Menu...");
    split_layout_menu_singleton = NULL;
}

GtkWidget* build_split_editor_tab(GtkWidget* window)
{
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

    // Title Container Box
    GtkWidget* title_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget* title_name_label = gtk_label_new("Game Name: ");
    GtkWidget* title_name_entry = gtk_entry_new();

    gtk_box_append(GTK_BOX(title_box), title_name_label);
    gtk_box_append(GTK_BOX(title_box), title_name_entry);

    gtk_widget_set_hexpand(title_name_entry, TRUE);

    gtk_box_append(GTK_BOX(box), title_box);

    // WR Time & Attempts Container Box

    GtkWidget* wr_and_attempts_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget* wr_time_label = gtk_label_new("World Record Time: ");
    GtkWidget* wr_time_entry = gtk_entry_new();
    GtkWidget* attempts_label = gtk_label_new("Attempts: ");
    GtkWidget* attempts_entry = gtk_entry_new();

    gtk_box_append(GTK_BOX(wr_and_attempts_box), wr_time_label);
    gtk_box_append(GTK_BOX(wr_and_attempts_box), wr_time_entry);
    gtk_box_append(GTK_BOX(wr_and_attempts_box), attempts_label);
    gtk_box_append(GTK_BOX(wr_and_attempts_box), attempts_entry);

    gtk_widget_set_hexpand(wr_time_entry, TRUE);
    gtk_widget_set_hexpand(attempts_entry, TRUE);

    gtk_box_append(GTK_BOX(box), wr_and_attempts_box);

    // Start Delay, Width, Height Container Box

    GtkWidget* delay_width_height_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget* start_delay_label = gtk_label_new("Start Delay: ");
    GtkWidget* start_delay_entry = gtk_entry_new();
    GtkWidget* width_label = gtk_label_new("Width: ");
    GtkWidget* width_entry = gtk_entry_new();
    GtkWidget* height_label = gtk_label_new("Height: ");
    GtkWidget* height_entry = gtk_entry_new();

    gtk_box_append(GTK_BOX(delay_width_height_box), start_delay_label);
    gtk_box_append(GTK_BOX(delay_width_height_box), start_delay_entry);
    gtk_box_append(GTK_BOX(delay_width_height_box), width_label);
    gtk_box_append(GTK_BOX(delay_width_height_box), width_entry);
    gtk_box_append(GTK_BOX(delay_width_height_box), height_label);
    gtk_box_append(GTK_BOX(delay_width_height_box), height_entry);

    gtk_widget_set_hexpand(start_delay_entry, TRUE);
    gtk_widget_set_hexpand(width_entry, TRUE);
    gtk_widget_set_hexpand(height_entry, TRUE);

    gtk_box_append(GTK_BOX(box), delay_width_height_box);

    // Splits Editor Container Box

    GtkWidget* splits_editor_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    GtkWidget* splits_editor_label = gtk_label_new("Splits");

    GtkWidget* box_separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_box_append(GTK_BOX(box), box_separator);

    // Splits Box

    GtkWidget* splits_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget* splits_table_container = gtk_scrolled_window_new();
    GtkWidget* splits_table = gtk_column_view_new(NULL);
    GtkWidget* edit_buttons_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(splits_table_container), splits_table);

    // Edit Buttons

    GtkWidget* move_up = gtk_button_new_with_label("Move Up");
    GtkWidget* move_down = gtk_button_new_with_label("Move Down");
    GtkWidget* add_segment = gtk_button_new_with_label("Add Segment");
    GtkWidget* remove_segment = gtk_button_new_with_label("Remove Segment");

    gtk_box_append(GTK_BOX(edit_buttons_box), move_up);
    gtk_box_append(GTK_BOX(edit_buttons_box), move_down);
    gtk_box_append(GTK_BOX(edit_buttons_box), add_segment);
    gtk_box_append(GTK_BOX(edit_buttons_box), remove_segment);

    gtk_box_append(GTK_BOX(splits_box), splits_table_container);

    GtkWidget* split_box_separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

    gtk_box_append(GTK_BOX(splits_box), split_box_separator);

    gtk_box_append(GTK_BOX(splits_box), edit_buttons_box);

    gtk_box_append(GTK_BOX(splits_editor_box), splits_editor_label);
    gtk_box_append(GTK_BOX(splits_editor_box), splits_box);

    gtk_widget_set_halign(splits_editor_label, GTK_ALIGN_START);

    gtk_widget_set_hexpand(splits_table_container, TRUE);

    gtk_widget_set_vexpand(splits_editor_box, TRUE);

    // Save & Quit Window Buttons

    GtkWidget* save_quit_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget* save_button = gtk_button_new_with_label("Save");
    GtkWidget* quit_button = gtk_button_new_with_label("Quit");

    gtk_box_append(GTK_BOX(save_quit_box), save_button);
    gtk_box_append(GTK_BOX(save_quit_box), quit_button);

    gtk_widget_set_halign(save_quit_box, GTK_ALIGN_END);

    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(gtk_window_destroy), window);

    gtk_box_append(GTK_BOX(box), splits_editor_box);
    gtk_box_append(GTK_BOX(box), save_quit_box);

    return box;
}

GtkWidget* build_layout_editor_tab(GtkWidget* window)
{
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    GtkWidget* component_list = gtk_list_box_new();

    gtk_box_append(GTK_BOX(box), component_list);

    GtkWidget* box_separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

    gtk_box_append(GTK_BOX(box), box_separator);

    for (int i = 0; ls_components[i].name != NULL; i++) {
        GtkWidget* label = gtk_label_new(ls_components[i].name);

        gtk_list_box_append(GTK_LIST_BOX(component_list), label);
    }

    GtkWidget* component_buttons_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);

    GtkWidget* move_up = gtk_button_new_with_label("Move Up");
    GtkWidget* move_down = gtk_button_new_with_label("Move Down");
    GtkWidget* toggle_visibility = gtk_toggle_button_new_with_label("Toggle Visibility");
    GtkWidget* separator = gtk_label_new("");
    GtkWidget* save_button = gtk_toggle_button_new_with_label("Save");
    GtkWidget* quit_button = gtk_toggle_button_new_with_label("Quit");

    gtk_widget_set_vexpand(separator, TRUE);

    gtk_box_append(GTK_BOX(component_buttons_container), move_up);
    gtk_box_append(GTK_BOX(component_buttons_container), move_down);
    gtk_box_append(GTK_BOX(component_buttons_container), toggle_visibility);
    gtk_box_append(GTK_BOX(component_buttons_container), separator);
    gtk_box_append(GTK_BOX(component_buttons_container), save_button);
    gtk_box_append(GTK_BOX(component_buttons_container), quit_button);

    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(gtk_window_destroy), window);

    gtk_box_append(GTK_BOX(box), component_buttons_container);

    gtk_widget_set_hexpand(component_list, TRUE);

    return box;
}

static void build_split_layout_dialog(GtkApplication* app, gpointer data)
{
    LOG_DEBUG("Opening Split Layout Menu Window...");

    if (split_layout_menu_singleton) {
        gtk_window_present(GTK_WINDOW(split_layout_menu_singleton));
        return;
    }

    GtkWindow* parent = gtk_application_get_active_window(app);
    GtkWidget* window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Split Layout Menu");

    gtk_window_set_transient_for(GTK_WINDOW(window), parent);
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(window), TRUE);

    gtk_window_set_application(GTK_WINDOW(window), app);
    split_layout_menu_singleton = window;
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 450);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect(window, "destroy", G_CALLBACK(on_split_layout_menu_window_destroy), NULL);

    // Tabs

    GtkWidget* tabs = gtk_notebook_new();

    GtkWidget* title_label = gtk_label_new("Splits");
    GtkWidget* title_label2 = gtk_label_new("Layout");

    GtkWidget* main_split_editor_tab = build_split_editor_tab(window);
    GtkWidget* main_layout_editor_tab = build_layout_editor_tab(window);

    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), main_split_editor_tab, title_label);
    gtk_notebook_append_page(GTK_NOTEBOOK(tabs), main_layout_editor_tab, title_label2);

    gtk_window_set_child(GTK_WINDOW(window), tabs);

    gtk_window_present(GTK_WINDOW(window));
}

void show_split_layout_menu(GSimpleAction* action, GVariant* parameter, gpointer app)
{
    if (parameter != NULL) {
        app = parameter;
    }

    build_split_layout_dialog(app, NULL);
}
