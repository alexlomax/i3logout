/* i3logout
 * Copyright (C) 2019 Alexander Lomtev <alexlomax@yandex.com>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include "commands.h"
#include "ui.h"

char *path = NULL;
GOptionEntry entries[] = {
  {"config", 'c', 0, G_OPTION_ARG_FILENAME, &path,
   "Path to config file",
   "PATH"},
  {NULL}
};

void
activate (GtkApplication * app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Choose action...");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_from_icon_name ("system-lock-screen",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Lock screen");
  g_signal_connect (button, "clicked", G_CALLBACK (lock_action), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill just 1
     cell horizontally and vertically (ie no spanning) */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-log-out",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Logout");
  g_signal_connect (button, "clicked", G_CALLBACK (logout_action), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill just 1
     cell horizontally and vertically (ie no spanning) */
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-reboot",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Reboot");
  g_signal_connect (button, "clicked", G_CALLBACK (reboot_action), NULL);

  /* Place the third button in the grid cell (2, 0), and make it fill just 1
     cell horizontally and vertically (ie no spanning) */
  gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-suspend",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Suspend");
  g_signal_connect (button, "clicked", G_CALLBACK (suspend_action), NULL);

  /* Place the fourth button in the grid cell (3, 0), and make it fill just 1
     cell horizontally and vertically (ie no spanning) */
  gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-hibernate",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Hibernate");
  g_signal_connect (button, "clicked", G_CALLBACK (hibernate_action), NULL);

  /* Place the fifth button in the grid cell (4, 0), and make it fill just 1
     cell horizontally and vertically (ie no spanning) */
  gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-shutdown",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Shutdown");
  g_signal_connect (button, "clicked", G_CALLBACK (shutdown_action), NULL);

  /* Place the sixth button in the grid cell (5, 0), and make it fill just 1
     cell horizontally and vertically (ie no spanning) */
  gtk_grid_attach (GTK_GRID (grid), button, 5, 0, 1, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked",
			    G_CALLBACK (gtk_widget_destroy), window);

  /* Place the Quit button in the grid cell (5, 1), and make it span 1
     columns. */
  gtk_grid_attach (GTK_GRID (grid), button, 5, 1, 1, 1);

  /* Now that we are done packing our widgets, we show them all in one go, by
     calling gtk_widget_show_all() on the window. This call recursively calls
     gtk_widget_show() on all widgets that are contained in the window,
     directly or indirectly. */
  gtk_widget_show_all (window);
}
