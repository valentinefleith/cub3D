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
#include "keycodes.h"

int	key_press(int keycode, t_maze *game)
{
	if (keycode == XK_s)
		game->player.keys_pressed[1] = true;
	else if (keycode == XK_w)
		game->player.keys_pressed[0] = true;
	else if (keycode == XK_a)
		game->player.keys_pressed[2] = true;
	else if (keycode == XK_d)
		game->player.keys_pressed[3] = true;
	else if (keycode == XK_Right)
		game->player.keys_pressed[5] = true;
	else if (keycode == XK_Left)
		game->player.keys_pressed[4] = true;
	else
		return (KO);
	return (SUCCESS);
}

int	key_release(int keycode, t_maze *game)
{
	if (keycode == XK_s)
		game->player.keys_pressed[1] = false;
	else if (keycode == XK_w)
		game->player.keys_pressed[0] = false;
	else if (keycode == XK_a)
		game->player.keys_pressed[2] = false;
	else if (keycode == XK_d)
		game->player.keys_pressed[3] = false;
	else if (keycode == XK_Right)
		game->player.keys_pressed[5] = false;
	else if (keycode == XK_Left)
		game->player.keys_pressed[4] = false;
	else
		return (KO);
	return (SUCCESS);
}

// int key_events(int keycode, t_maze *maze)
// {
// 	if (keycode == XK_s || keycode == XK_w || keycode == XK_a || keycode == XK_d)
// 		return (move_player(maze, keycode, maze->player.looking_angle));
// 	if (keycode == XK_Right || keycode == XK_Left)
// 		return (rotate_player(maze, keycode));
// 	return 0;
// }