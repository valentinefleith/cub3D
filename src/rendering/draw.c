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

// static double	setup_texture_coord(t_maze *maze, t_vector wall_point, double wall_height)
// {
// 	double	pixel_scaling;
// 	// Determiner la position exacte où le rayon frappe le mur == position relative
// 	if (maze->horizontal_point) // Point d'intersection du mur etait à l'horizontal
// 		maze->texture.x = fmodf(wall_point.x * (double)(maze->texture.width / TILE_SIZE), (double)maze->texture.width);
// 	else
// 		maze->texture.x = fmodf(wall_point.y * (double)(maze->texture.width / TILE_SIZE), (double)maze->texture.width);
// 	if (maze->texture.x < 0)
// 		maze->texture.x += maze->texture.width;
// 	// On veut trouver la position dans la texture et scale selon la hauteur de la ligne à dessinner
// 	maze->texture.y = 0;
// 	pixel_scaling = (double)maze->texture.height / wall_height;
// 	return (pixel_scaling);
// }

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
	// texture = get_texture(maze);
	// scale = setup_texture_coord(maze, wall_point, wall_height);
	scale = (double)texture.height / wall_height;
	draw_ceilling(maze, x, y);
	texture.y = ((double)y - ((HEIGHT / 2) - (wall_height / 2))) * scale;
	while (y < end_y)
	{
		px_color = get_px_color(texture, texture.x, texture.y);
		if (px_color > 0)
			my_mlx_pixel_put(&(maze->img), x, y, px_color);
		texture.y += scale;
		y++;
	}
	draw_floor(maze, x, end_y);
}

// On va chercher dans l'image texturée le pixel exact de la couleur qui nous interresse pour reconstituer l'image
int	get_px_color(t_img texture, int x, int y)
{
	uint8_t *pixel;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return (-1);
	pixel = (uint8_t *)(texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8)));
	return *(int32_t *)pixel;
	// return (*(int *)(texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8))));
}

void	draw_floor(t_maze *maze, int x, int start)
{
	while (start < HEIGHT)
	{
		my_mlx_pixel_put(&(maze->img), x, start, GREY);
		start++;
	}
}

void	draw_ceilling(t_maze *maze, int x, int end)
{
	int	start;

	start = 0;
	while (start < end)
	{
		my_mlx_pixel_put(&(maze->img), x, start, BLACK);
		start++;
	}
}
