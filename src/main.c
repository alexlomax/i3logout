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

#include <gtk/gtk.h>
#include <getopt.h>
#include "commands.h"
#include "config.h"
#include "ui.h"

#define VERSION "v0.1.1"

const char *program_name;

/* Display information about the use of the program in STREAM
 * (usually stdout or stderr) and exit with issuing the EXIT_CODE code.
 * Return to main () function does not occur.
 */
void
print_usage (FILE * stream, int exit_code)
{
/* *INDENT-OFF* */
  fprintf (stream, "Usage: %s [options] <path>\n", program_name);
  fprintf (stream, "  -c PATH --config=PATH  Path to configuration file\n"
	           "  -v --version           Version of the program\n"
	           "  -h --help              Display this usage information\n");
/* *INDENT-ON* */
  exit (exit_code);
}



int
main (int argc, char **argv)
{
  GtkApplication *app;
  int next_option;
  int status;

  /* Short options. */
  const char *const short_options = "c:vh";
  /* Long options. */
  const struct option long_options[] = {
    {"help", 0, NULL, 'h'},
    {"config", 1, NULL, 'c'},
    {"version", 0, NULL, 'v'},
    {NULL, 0, NULL, 0}
  };

  /* Remember the name of the program that will be included in the message. */
  program_name = argv[0];

  do
    {
      next_option =
	getopt_long (argc, argv, short_options, long_options, NULL);
      switch (next_option)
	{
	case 'c':
	  /* This option takes an argument - a path to configuration file. */
	  path = optarg;
	  printf ("* Debug main.c path: %s\n", path);
          parse_config(path);
	  break;
	case 'v':
	  printf ("%s\n", VERSION);
	  exit (0);
	  break;
	case 'h':
	  /* The user has requested information about the use of the
	   * program, you need to output it to the stdout stream and
	   * exit with code 0 (normal termination).
	   */
	  print_usage (stdout, 0);
	  break;
	case '?':		/* User entered invalid option. */
	  /* Write information about the use of the program in the
	   * stderr stream and exits with the issuance of the
	   * code 1 (crash).
	   */
	  print_usage (stderr, 1);
	  break;
	case -1:		/* No more options. */
	  break;
	default:		/* Some unexpected result. */
	  abort ();
	}
    }
  while (next_option != -1);

  printf ("* Debug main.c path: %s\n", path);
  parse_config(path);

  app = gtk_application_new ("com.yandex.alexlomax.i3logout",
  			     G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), 0, NULL);

  g_object_unref (app);
  cleanup_config();

  return status;
}
