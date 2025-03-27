/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:19:21 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 18:23:09 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_x_coord(t_img *texture, t_vector wall_point, \
			bool horizontal_point, double angle)
{
	if (horizontal_point)
		texture->x = fmodf(wall_point.x * ((double)texture->width / TILE_SIZE),
				(double)texture->width);
	else
		texture->x = fmodf(wall_point.y * ((double)texture->width / TILE_SIZE),
				(double)texture->width);
	if (texture->x < 0)
		texture->x += (double)texture->width;
	if ((horizontal_point && get_horizontal_direction(angle) != facing_up)
		|| (!horizontal_point && get_vertical_direction(angle) == facing_left))
		texture->x = (double)texture->width - texture->x;
	texture->y = 0;
}

static t_img	get_wall_texture(t_maze *game, double angle)
{
	t_img	texture;

	if (game->wall_type == 2)
		return (game->texture[4]);
	if (game->horizontal_point)
	{
		if (get_horizontal_direction(angle) == facing_up)
			texture = game->texture[west];
		else
			texture = game->texture[east];
	}
	else
	{
		if (get_vertical_direction(angle) == facing_left)
			texture = game->texture[north];
		else
			texture = game->texture[south];
	}
	return (texture);
}

t_img	setup_texture(t_maze *game, t_vector wall_point, double angle)
{
	t_img	texture;

	texture = get_wall_texture(game, angle);
	setup_x_coord(&texture, wall_point, game->horizontal_point, angle);
	return (texture);
}
