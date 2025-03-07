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
	if (keycode == XK_Escape)
		exit_program(game, 0);
	if (keycode == XK_w)
		game->player.keys_pressed[front] = true;
	else if (keycode == XK_s)
		game->player.keys_pressed[back] = true;
	else if (keycode == XK_a)
		game->player.keys_pressed[left] = true;
	else if (keycode == XK_d)
		game->player.keys_pressed[right] = true;
	else if (keycode == XK_Right)
		game->player.keys_pressed[right_rotation] = true;
	else if (keycode == XK_Left)
		game->player.keys_pressed[left_rotation] = true;
	else if (keycode == XK_m && !game->minimap_key)
		game->minimap_key = true;
	else if (keycode == XK_m && game->minimap_key)
		game->minimap_key = false;
	else
		return (KO);
	return (SUCCESS);
}

int	key_release(int keycode, t_maze *game)
{
	if (keycode == XK_w)
		game->player.keys_pressed[front] = false;
	else if (keycode == XK_s)
		game->player.keys_pressed[back] = false;
	else if (keycode == XK_a)
		game->player.keys_pressed[left] = false;
	else if (keycode == XK_d)
		game->player.keys_pressed[right] = false;
	else if (keycode == XK_Right)
		game->player.keys_pressed[right_rotation] = false;
	else if (keycode == XK_Left)
		game->player.keys_pressed[left_rotation] = false;
	else
		return (KO);
	return (SUCCESS);
}
