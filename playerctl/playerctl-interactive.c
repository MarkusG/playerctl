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

#include "playerctl-player.h"

int init_interactive(PlayerctlPlayer *player) {
	// get input character-by-character
	struct termios old, new;
	tcgetattr(STDIN_FILENO, &new);
	old = new;
	new.c_lflag &= ~ICANON; // canonical mode (char by char)
	new.c_lflag &= ~ECHO; // echo off
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	char c;
	while ((c = getchar())) {
		if (c == ' ') {
			 playerctl_player_play_pause(player, NULL);
		}
		// arrow key codes are in the form \033[X where X is direction
		if (c == '\033') {
			getchar(); // skip [
			switch (getchar()) {
				case 65:
					printf("UP\n");
					break;
				case 66:
					printf("DOWN\n");
					break;
				case 67:
					printf("RIGHT\n");
					break;
				case 68:
					printf("LEFT\n");
					break;
			}
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return 0;
}
