/*
 * This file is part of playerctl.
 *
 * playerctl is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * playerctl is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with playerctl If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright © 2014, Tony Crisci and contributors
 */

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int handle_interactive(void) {
	// get input character-by-character
	struct termios old, new;
	tcgetattr(STDIN_FILENO, &new);
	old = new;
	new.c_lflag &= ~ICANON; // canonical mode (char by char)
	new.c_lflag &= ~ECHO; // echo off
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	char c;
	while ((c = getchar())) {
		printf("%d\n", c);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return 0;
}
