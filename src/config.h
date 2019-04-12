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
#define MAXLEN 100

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

extern struct config conf;

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
write_config (char *path);

void
read_config (char *path);


#endif /* SRC_CONFIG_H_ */
