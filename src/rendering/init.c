/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:28:56 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 21:30:37 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_maze(t_maze *maze) {
	t_img img;

	img.img = mlx_new_image(maze->mlx, WIDTH, HEIGHT);
	if (!img.img)
	{
		free_window(maze);
		return MLX_ERROR;
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	maze->img = img;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			my_mlx_pixel_put(&img, i, j, YELLOW);
		}
	}
	mlx_put_image_to_window(maze->mlx, maze->win, img.img, 0, 0);
	return SUCCESS;
}

void init_hook(t_maze *maze) {
	mlx_hook(maze->win, 17, 0, exit_program, maze);
}
