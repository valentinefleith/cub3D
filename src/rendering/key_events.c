/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:17:35 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 22:25:31 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int move_player(t_maze *maze, int keycode) {
	if (keycode == KEY_RIGHT)
		maze->player.pos.x += PLAYER_MOVE_PX;
	else if (keycode == KEY_LEFT)
		maze->player.pos.x -= PLAYER_MOVE_PX;
	else if (keycode == KEY_UP)
		maze->player.pos.y -= PLAYER_MOVE_PX;
	else if (keycode == KEY_DOWN)
		maze->player.pos.y += PLAYER_MOVE_PX;
	render_one_frame(maze, false);
	return SUCCESS;
}


int key_events(int keycode, t_maze *maze) {
	if (keycode == KEY_RIGHT || keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT)
		return (move_player(maze, keycode));
	return 0;
}
