/* i3logout - Simple i3 logout dialog written in C and Gtk3
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

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#define MAXLEN 100

void
lock_action (void)
{
  system ("uname -a");
}

void
logout_action (void)
{
  g_print ("Logout");
}

void
reboot_action (void)
{
  g_print ("Reboot\n");
}

void
suspend_action (void)
{
  g_print ("Suspend\n");
}

void
hibernate_action (void)
{
  g_print ("Hibernate\n");
}

void
shutdown_action (void)
{
  g_print ("Shutdown\n");
}

struct config
{
  char lock_command[MAXLEN];
  char logout_command[MAXLEN];
  char reboot_command[MAXLEN];
  char suspend_command[MAXLEN];
  char hibernate_command[MAXLEN];
  char shutdown_command[MAXLEN];
};

void
read_config (const char *value);

void
write_config (const char *value)
{
  /* Set default configuration file options */
  struct config conf =
    { .lock_command = "uname -a", .logout_command = "uname -a",
	.reboot_command = "uname -a", .suspend_command = "uname -a",
	.hibernate_command = "uname -a", .shutdown_command = "uname -a" };

  FILE *file = fopen (value, "w");

  fputs ("lock_command=", file);
  fputs (conf.lock_command, file);
  fputs ("\n", file);

  fputs ("logout_command=", file);
  fputs (conf.logout_command, file);
  fputs ("\n", file);

  fputs ("reboot_command=", file);
  fputs (conf.reboot_command, file);
  fputs ("\n", file);

  fputs ("suspend_command=", file);
  fputs (conf.suspend_command, file);
  fputs ("\n", file);

  fputs ("hibernate_command=", file);
  fputs (conf.hibernate_command, file);
  fputs ("\n", file);

  fputs ("shutdown_command=", file);
  fputs (conf.shutdown_command, file);

  fclose (file);

  read_config (value);
}

void
read_config (const char *value)
{
  char str[MAXLEN];
  int i = 0;
  struct config conf;
  FILE *file = fopen (value, "r");

  if (!file)
    {
      g_print ("Configuration file not found\n");
      write_config (value);
    }
  else
    {

      while (fgets (str, MAXLEN, file) != NULL)
	{
	  char *line;
	  line = strstr (str, "=");
	  line = line + strlen ("=");

	  if (i == 0)
	    strcpy (conf.lock_command, line);
	  else if (i == 1)
	    strcpy (conf.logout_command, line);
	  else if (i == 2)
	    strcpy (conf.reboot_command, line);
	  else if (i == 3)
	    strcpy (conf.suspend_command, line);
	  else if (i == 4)
	    strcpy (conf.hibernate_command, line);
	  else if (i == 5)
	    strcpy (conf.shutdown_command, line);
	  i++;
	}
      fclose (file);
    }

  printf ("%s", conf.lock_command);
  printf ("%s", conf.logout_command);
  printf ("%s", conf.reboot_command);
  printf ("%s", conf.suspend_command);
  printf ("%s", conf.hibernate_command);
  printf ("%s", conf.shutdown_command);
}

gboolean
parse (const char *key, const char *value, gpointer user_data, GError **error)
{
  read_config (value);

  return TRUE;
}

/*  const gchar *long_name
 *  gchar        short_name
 *  flags
 *  GOptionArg   arg
 *  gpointer     arg_data
 *  const gchar *description
 *  const gchar *arg_description
 */
static GOptionEntry entries[] =
  {
    { "config", 'c', 0, G_OPTION_ARG_CALLBACK, &parse, "Path to config file",
	"PATH" } };

static void
activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW(window), "Choose action...");
  gtk_container_set_border_width (GTK_CONTAINER(window), 10);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER(window), grid);

  button = gtk_button_new_from_icon_name ("system-lock-screen",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Lock screen");
  g_signal_connect(button, "clicked", G_CALLBACK (lock_action), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID(grid), button, 0, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-log-out",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Logout");
  g_signal_connect(button, "clicked", G_CALLBACK (logout_action), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID(grid), button, 1, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-reboot",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Reboot");
  g_signal_connect(button, "clicked", G_CALLBACK (reboot_action), NULL);

  /* Place the third button in the grid cell (2, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID(grid), button, 2, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-suspend",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Suspend");
  g_signal_connect(button, "clicked", G_CALLBACK (suspend_action), NULL);

  /* Place the fourth button in the grid cell (3, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID(grid), button, 3, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-hibernate",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Hibernate");
  g_signal_connect(button, "clicked", G_CALLBACK (hibernate_action), NULL);

  /* Place the fifth button in the grid cell (4, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID(grid), button, 4, 0, 1, 1);

  button = gtk_button_new_from_icon_name ("system-shutdown",
					  GTK_ICON_SIZE_DIALOG);
  gtk_widget_set_tooltip_text (button, "Shutdown");
  g_signal_connect(button, "clicked", G_CALLBACK (shutdown_action), NULL);

  /* Place the sixth button in the grid cell (5, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID(grid), button, 5, 0, 1, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy),
			   window);

  /* Place the Quit button in the grid cell (5, 1), and make it
   * span 1 columns.
   */
  gtk_grid_attach (GTK_GRID(grid), button, 5, 1, 1, 1);

  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
  gtk_widget_show_all (window);

}

int
main (int argc, char **argv)
{
  GtkApplication *app;
  GOptionContext *context;
  GError *error = NULL;
  int status;

  app = gtk_application_new ("com.yandex.alexlomax.i3logout",
			     G_APPLICATION_FLAGS_NONE);

  /* Create custom command-line options */
  context = g_option_context_new ("- simple i3 logout dialog written "
				  "in C and Gtk3");
  g_option_context_add_main_entries (context, entries, NULL);
  g_option_context_add_group (context, gtk_get_option_group (TRUE));
  if (!g_option_context_parse (context, &argc, &argv, &error))
    {
      g_print ("option parsing failed: %s\n", error->message);
      exit (1);
    }

  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION(app), argc, argv);
  g_object_unref (app);

  return status;
}
