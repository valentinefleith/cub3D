/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:17:35 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/11 21:34:15 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int move_player(t_maze *maze, int keycode) {
	if (keycode == XK_d)
		maze->player.pos.x += PLAYER_MOVE_PX;
	else if (keycode == XK_a)
		maze->player.pos.x -= PLAYER_MOVE_PX;
	else if (keycode == XK_w)
		maze->player.pos.y -= PLAYER_MOVE_PX;
	else if (keycode == XK_s)
		maze->player.pos.y += PLAYER_MOVE_PX;
	render_one_frame(maze, false);
	return SUCCESS;
}

static int rotate_player(t_maze *maze, int keycode) {
	if (keycode == XK_Left)
		maze->player.looking_angle = fmod(maze->player.looking_angle + 0.1, 2 * M_PI) ;
	else
		maze->player.looking_angle = fmod(maze->player.looking_angle - 0.1, 2 * M_PI) ;
	render_one_frame(maze, false);
	return SUCCESS;
}

int key_events(int keycode, t_maze *maze) {
	if (keycode == XK_s || keycode == XK_w || keycode == XK_a || keycode == XK_d)
		return (move_player(maze, keycode));
	if (keycode == XK_Right || keycode == XK_Left)
		return (rotate_player(maze, keycode));
	return 0;
}
