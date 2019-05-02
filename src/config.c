/* i3logout - Simple i3 logout dialog written in C and Gtk3.
 * Copyright (C) 2019 Alexander Lomtev <alexlomax@yandex.com>.

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

#include "config.h"

#include <libconfig.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *path = NULL;

char *lock_cmd;
char *logout_cmd;
char *reboot_cmd;
char *suspend_cmd;
char *hibernate_cmd;
char *shutdown_cmd;

void
cleanup_config (void)
{
  free (commands.lock);
  free (commands.logout);
  free (commands.reboot);
  free (commands.suspend);
  free (commands.hibernate);
  free (commands.shutdown);
}

int
parse_config (char *path)
{
  config_t cfg;
  const char *value;

  /* If the program is started without the -c option, set the default path to
   * the configuration file.
   */
  if (path == NULL)
    {
      /* Using the XDG configuration specification. */
      path = "/etc/xdg/i3logout/i3logout.conf";
    }

  config_init (&cfg);

  printf ("* Debug config.c path: %s\n", path);

  /* Read the file. If there is an error, report it and exit. */
  if (!config_read_file (&cfg, path))
    {
      fprintf (stderr, "%s:%d - %s\n", config_error_file (&cfg),
	       config_error_line (&cfg), config_error_text (&cfg));
      config_destroy (&cfg);
      return (EXIT_FAILURE);
    }

  /* Filling up the commands configuration structure */
  if (config_lookup_string (&cfg, "commands.lock", &value))
    {
      commands.lock = malloc (strlen (value) + 1);
      strcpy (commands.lock, value);
    }
  else if (config_lookup_string (&cfg, "commands.logout", &value))
    {
      commands.logout = malloc (strlen (value) + 1);
      strcpy (commands.logout, value);
    }
  else if (config_lookup_string (&cfg, "commands.reboot", &value))
      {
        commands.reboot = malloc (strlen (value) + 1);
        strcpy (commands.reboot, value);
      }
  else if (config_lookup_string (&cfg, "commands.suspend", &value))
      {
        commands.suspend = malloc (strlen (value) + 1);
        strcpy (commands.suspend, value);
      }
  else if (config_lookup_string (&cfg, "commands.hibernate", &value))
      {
        commands.hibernate = malloc (strlen (value) + 1);
        strcpy (commands.hibernate, value);
      }
  else if (config_lookup_string (&cfg, "commands.shutdown", &value))
      {
        commands.shutdown = malloc (strlen (value) + 1);
        strcpy (commands.shutdown, value);
      }

  config_destroy (&cfg);
  return (EXIT_SUCCESS);
}
