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

int	init_keys(t_maze *game)
{
	int	i;

	if (!game)
		return (KO);
	i = 0;
	while (i < 6)
	{
		game->player.keys_pressed[i] = false;
		i++;
	}
	return (SUCCESS);
}

int	key_press(int keycode, t_maze *game)
{
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
