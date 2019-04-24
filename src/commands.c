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

#include "commands.h"

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

/* TODO Create lock_action(). */
void
lock_action (void)
{
  printf ("* Debug lock_action (): %s\n", lock_cmd);
  system (lock_cmd);
}

/* TODO Create logout_action(). */
void
logout_action (void)
{
  system ("echo '* Debug: logout_action ()'");
}

/* TODO Create reboot_action(). */
void
reboot_action (void)
{
  system ("echo '* Debug: reboot_action ()'");
}

/* TODO Create suspend_action(). */
void
suspend_action (void)
{
  system ("echo '* Debug: suspend_action()'");
}

/* TODO Create hibernate_action(). */
void
hibernate_action (void)
{
  system ("echo '* Debug: hibernate_action ()'");
}

/* TODO Create shutdown_action(). */
void
shutdown_action (void)
{
  system ("echo '* Debug: shutdown_action ()'");
}
