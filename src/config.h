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

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

extern char *path;

/* A structure representing commands configuration */
typedef struct
{
  char *lock;
  char *logout;
  char *reboot;
  char *suspend;
  char *hibernate;
  char *shutdown;
} commands_t;

commands_t commands;

void cleanup_config (void);

int parse_config (char *path);

#endif /* SRC_CONFIG_H_ */
