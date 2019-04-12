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

#include <string.h>
#include <gtk/gtk.h>
#include "commands.h"
#include "config.h"
#include "ui.h"

int
main (int argc, char **argv)
{
  GtkApplication *app;
  GOptionContext *context;
  GError *error = NULL;
  int status;
  int arg_count = argc;		/* We copy argc because
				   g_option_context_parse () modifies it */

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
  else if (arg_count < 3)
    {				/* Set default config file path if the amount 
				   of args is too few */
      path = getenv ("HOME");
      if (path != NULL)
	{
	  strcat (path, "/.config/i3logout/config");
	}
      else
	{
	  perror ("getenv");
	  exit (1);
	}
    }

  printf ("* Debug: main () path: %s\n", path);
  read_config (path);

  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
