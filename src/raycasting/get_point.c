/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:01:41 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 17:04:32 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	get_first_y_point(t_vector player, double angle, t_dir direction)
{
	t_vector	first_point;

	if (direction == facing_left)
		first_point.x = floor(player.x / TILE_SIZE) * TILE_SIZE - 0.00001;
	else
		first_point.x = floor(player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	first_point.y = player.y - (player.x - first_point.x) * tan(angle);
	return (first_point);
}

t_vector	get_first_x_point(t_vector player_pos, double angle, \
			t_dir direction)
{
	t_vector	first_point;

	if (direction == facing_up)
		first_point.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE - 0.00001;
	else
		first_point.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	first_point.x = player_pos.x - (player_pos.y - first_point.y) / tan(angle);
	return (first_point);
}

t_vector	get_point_horizon(t_map *map, double angle, t_dir direction, \
			t_vector point)
{
	double	x_step;
	double	y_step;

	y_step = TILE_SIZE;
	if (direction == facing_up)
		y_step *= -1;
	x_step = TILE_SIZE / tan(angle);
	if (get_vertical_direction(angle) == facing_left && x_step > 0)
		x_step *= -1;
	if (get_vertical_direction(angle) == facing_right && x_step < 0)
		x_step *= -1;
	while (!is_wall_point(map, point))
	{
		point.x += x_step;
		point.y += y_step;
	}
	return (point);
}

t_vector	get_point_vert(t_map *map, double angle, t_dir direction, \
			t_vector point)
{
	double	x_step;
	double	y_step;

	x_step = TILE_SIZE;
	if (direction == facing_left)
		x_step *= -1;
	y_step = TILE_SIZE * tan(angle);
	if ((get_horizontal_direction(angle) == facing_up && y_step > 0)
		|| (get_horizontal_direction(angle) == facing_down && y_step < 0))
		y_step *= -1;
	while (!is_wall_point(map, point))
	{
		point.x += x_step;
		point.y += y_step;
	}
	return (point);
}
