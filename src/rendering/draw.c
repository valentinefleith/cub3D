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

static int	find_color(t_img texture, double wall_height, int wall_type, t_map map)
{
	int			pixel_color;

	pixel_color = get_px_color(texture, texture.x, texture.y);
	if (wall_type == 2 && pixel_color == -16777216)
	{
		if (texture.y <= texture.height / 3)
			pixel_color = map.color_sequence[0];
		else if (texture.y <= texture.height / 1.5)
			pixel_color = map.color_sequence[1];
		else if (texture.y > texture.height / 1.5)
			pixel_color = map.color_sequence[2];
	}
	if (wall_type == 3 && pixel_color == (int)map.target_color)
		pixel_color = map.color_sequence[0];
	if (wall_type == 4 && pixel_color == (int)map.target_color)
		pixel_color = map.color_sequence[1];
	if (wall_type == 5 && pixel_color == (int)map.target_color)
		pixel_color = map.color_sequence[2];
	pixel_color = shading_color(pixel_color, wall_height, HEIGHT);
	return (pixel_color);
}

void	draw_wall(t_maze *maze, t_img texture, double wall_height, int x)
{
	int		current_y;
	int		end_y;
	int		color;
	double	scale;

	current_y = (HEIGHT / 2) - (wall_height / 2);
	if (current_y < 0)
		current_y = 0;
	end_y = (HEIGHT / 2) + (wall_height / 2);
	if (HEIGHT < end_y)
		end_y = HEIGHT;
	scale = (double)texture.height / (wall_height - 1);
	draw_ceilling(maze, x, current_y);
	texture.y = ((double)current_y - ((HEIGHT / 2) - (wall_height / 2))) * scale;
	while (current_y < end_y)
	{
		color = find_color(texture, wall_height, maze->wall_type, maze->map);
		if (color > 0)
			my_mlx_pixel_put(&(maze->img), x, current_y, color);
		texture.y += scale;
		current_y++;
	}
	draw_floor(maze, x, end_y);
}

void	draw_floor(t_maze *maze, int x, int start)
{
	int		color;
	double	intensity;

	color = maze->map.floor_color;
	while (start < HEIGHT)
	{
		intensity = ((double)start / HEIGHT) - 0.8;
		if (intensity > 0.0)
			intensity = 0.0;
		my_mlx_pixel_put(&(maze->img), x, start, shading_color(color, intensity, 0.8));
		start++;
	}
}

void	draw_ceilling(t_maze *maze, int x, int end)
{
	int		start;
	int		color;
	double	intensity;

	start = 0;
	color = maze->map.ceilling_color;
	while (start <= end)
	{
		intensity = 0.8 - ((double)start / (HEIGHT / 2));
		if (intensity < 0.0)
			intensity = 0.0;
		my_mlx_pixel_put(&(maze->img), x, start, shading_color(color, intensity, 0.8));
		start++;
	}
}
