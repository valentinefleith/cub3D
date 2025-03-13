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
	else if ((keycode == XK_m || keycode == XK_Up) && !game->minimap_key)
		game->minimap_key = true;
	else if ((keycode == XK_m || keycode == XK_Up) && game->minimap_key)
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

int mouse_move(int x, int y, t_maze *game)
{
	(void)y;
	if (x == WIDTH / 2)
		return (SUCCESS);
	if (x <= (WIDTH / 3) && x >= 0)
	{
		game->player.looking_angle -= 0.010;
		if (game->player.looking_angle < 0)
			game->player.looking_angle += 2.0 * M_PI;
	}
	if (x >= (WIDTH / 1.5) && x <= WIDTH)
	{
		game->player.looking_angle += 0.010;
		if (game->player.looking_angle > 2.0 * M_PI)
			game->player.looking_angle -= 2.0 * M_PI;
	}
	if (x < 0)
		mlx_mouse_move(game->mlx, game->win, 0, y);
	if (x > WIDTH)
		mlx_mouse_move(game->mlx, game->win, WIDTH, y);
    render_one_frame(game, false);
    return (0);
}
