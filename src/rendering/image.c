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

t_img	init_img_struct(void)
{
	t_img	img;

	img.img = NULL; 
	img.addr = NULL;
	img.bits_per_pixel = 0;
	img.line_length = 0;
	img.endian = 0;
	img.width = 0;
	img.height = 0;
	img.x = 0;
	img.y = 0;
	return (img);
}

int	render_one_frame(t_maze *game, bool init)
{
	t_img	img;

	if (!init)
		mlx_destroy_image(game->mlx, game->img.img);
	img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img.img)
	{
		free_window(game);
		return (MLX_ERROR);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		&img.endian);
	game->img = img;
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	return (SUCCESS);
}
