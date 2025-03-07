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

// On va chercher dans l'image texturée le pixel exact de la couleur qui nous interresse pour reconstituer l'image
int	get_px_color(t_img texture, int x, int y)
{
	uint8_t *pixel;

	if (x > texture.width || x < 0 || y > texture.height || y < 0)
		return (-1);
	pixel = (uint8_t *)(texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8)));
	return *(int32_t *)pixel;
	// return (*(int *)(texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8))));
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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		&img.endian);
	if (!img.addr)
		exit_program(game, 1);
	game->img = img;
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	return (SUCCESS);
}
