/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:34:16 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 21:53:23 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	render_one_frame(t_maze *maze, bool initialization)
{
	t_img	img;
	t_img	texture;

	if (!initialization)
	{
		mlx_destroy_image(maze->mlx, maze->img.img);
	}
	else
	{
		texture.img = mlx_xpm_file_to_image(maze->mlx, "./assets/wolf.xpm", &texture.width, &texture.height);
		if (!texture.img)
		{
			free_window(maze);
			return (MLX_ERROR);
		}
		texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
		maze->texture = texture;
	}
	img.img = mlx_new_image(maze->mlx, WIDTH, HEIGHT);
	if (!img.img)
	{
		free_window(maze);
		return (MLX_ERROR);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		&img.endian);
	maze->img = img;
	raycasting(maze);
	mlx_put_image_to_window(maze->mlx, maze->win, img.img, 0, 0);
	return (SUCCESS);
}
