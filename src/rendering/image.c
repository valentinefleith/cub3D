/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:34:16 by vafleith          #+#    #+#             */
/*   Updated: 2025/03/27 18:19:02 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_px_color(t_img texture, int x, int y)
{
	uint8_t	*pixel;
	int		bpp;

	if (x > texture.width || x < 0 || y > texture.height || y < 0)
		return (-1);
	bpp = texture.bits_per_pixel / 8;
	pixel = (uint8_t *)(texture.addr + (y * texture.line_length + x * bpp));
	return (*(int32_t *)pixel);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	if (!img.addr)
		exit_program(game, 1);
	game->img = img;
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	return (SUCCESS);
}
