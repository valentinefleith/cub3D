/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:43:50 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/12 10:32:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	shading_color(int color, double dist, double max_dist)
{
	int		r;
	int		g;
	int		b;
	double	intensity;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	intensity = 0.6 + (dist / max_dist);
	if (intensity > 1.0)
		intensity = 1.0;
	r *= intensity;
	g *= intensity;
	b *= intensity;
	return ((r << 16) | (g << 8) | b);
}

void	draw_wall(t_maze *maze, t_img texture, double wall_height, int x)
{
	int		y;
	int		end_y;
	int		px_color;
	double	scale;

	y = (HEIGHT / 2) - (wall_height / 2);
	if (y < 0)
		y = 0;
	end_y = (HEIGHT / 2) + (wall_height / 2);
	if (HEIGHT < end_y)
		end_y = HEIGHT;
	scale = (double)texture.height / (wall_height - 1);
	draw_ceilling(maze, x, y);
	texture.y = ((double)y - ((HEIGHT / 2) - (wall_height / 2))) * scale;
	double shading_factor = wall_height / (double)HEIGHT;
    if (shading_factor > 1.0)
		shading_factor = 1.0;
	while (y < end_y)
	{
		px_color = get_px_color(texture, texture.x, texture.y);
		px_color = shading_color(px_color, wall_height, HEIGHT);
		if (px_color > 0)
			my_mlx_pixel_put(&(maze->img), x, y, px_color);
		texture.y += scale;
		y++;
	}
	draw_floor(maze, x, end_y);
}

void	draw_floor(t_maze *maze, int x, int start)
{
	while (start < HEIGHT)
	{
		my_mlx_pixel_put(&(maze->img), x, start, maze->map.floor_color);
		start++;
	}
}

void	draw_ceilling(t_maze *maze, int x, int end)
{
	int	start;
	int	color;

	start = 0;
	color = maze->map.ceilling_color;
	while (start <= end)
	{
		color = shading_color(color, (double)end, (double)start);
		my_mlx_pixel_put(&(maze->img), x, start, color);
		start++;
	}
}
