#pragma once

#include <gtk/gtk.h>

typedef struct LSGuiSplitLayout {
    GtkWidget* widget;
} LSGuiSplitLayout;

void show_split_layout_menu(GSimpleAction* action, GVariant* parameter, gpointer app);
