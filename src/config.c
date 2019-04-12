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
#include <stdio.h>

#include "config.h"

/* TODO Remove this temporary constant */
#define COMMAND "uname -a"

#define MAXLEN 100
#define DELIM "="

/* Set default configuration file options */
struct config conf = {
  .lock_command = COMMAND,
  .logout_command = COMMAND,
  .reboot_command = COMMAND,
  .suspend_command = COMMAND,
  .hibernate_command = COMMAND,
  .shutdown_command = COMMAND
};

void
write_config (char *path)
{

  FILE *file = fopen (path, "w");

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

  printf ("* Debug write_config (): lock_command: %s\n",
	  conf.lock_command);
  printf ("* Debug write_config (): logout_command: %s\n",
	  conf.logout_command);
  printf ("* Debug write_config (): reboot_command: %s\n",
	  conf.reboot_command);
  printf ("* Debug write_config (): suspend_command: %s\n",
	  conf.suspend_command);
  printf ("* Debug write_config (): hibernate_command: %s\n",
	  conf.hibernate_command);
  printf ("* Debug write_config (): shutdown_command: %s\n",
	  conf.shutdown_command);
}

void
read_config (char *path)
{
  FILE *file = fopen (path, "r");
  char str[MAXLEN];
  int i = 0;

  if (!file)
    {
      /* File not found! */
      perror (path);
      write_config (path);
    }
  else
    {

      while (fgets (str, MAXLEN, file) != NULL)
	{
	  char *line;
	  line = strstr (str, DELIM);
	  line = line + strlen (DELIM);

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

      printf ("* Debug read_config (): lock_command: %s",
	      conf.lock_command);
      printf ("* Debug read_config (): logout_command: %s",
	      conf.logout_command);
      printf ("* Debug read_config (): reboot_command: %s",
	      conf.reboot_command);
      printf ("* Debug read_config (): suspend_command: %s",
	      conf.suspend_command);
      printf ("* Debug read_config (): hibernate_command: %s",
	      conf.hibernate_command);
      printf ("* Debug read_config (): shutdown_command: %s\n",
	      conf.shutdown_command);
    }
}


