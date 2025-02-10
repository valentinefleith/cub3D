/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:18:47 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 18:45:45 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int free_window(t_maze* maze) {
	mlx_destroy_window(maze->mlx, maze->win);
	mlx_destroy_display(maze->mlx);
	free(maze->mlx);
	return SUCCESS;
}

static int exit_program(t_maze *maze) {
	mlx_destroy_image(maze->mlx, maze->img.img);
	free_window(maze);
	exit(SUCCESS);
	return SUCCESS;
}

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int init_maze(t_maze *maze) {
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

static void init_hook(t_maze *maze) {
	mlx_hook(maze->win, 17, 0, exit_program, maze);
}

int main() {
	t_maze maze;

	maze.mlx = mlx_init();
	if (!maze.mlx)
		return MLX_ERROR;
	maze.win = mlx_new_window(maze.mlx, WIDTH, HEIGHT, "cub3D");
	if (!maze.win) {
		mlx_destroy_display(maze.mlx);
		free(maze.mlx);
		return MLX_ERROR;
	}
	if (init_maze(&maze) == MLX_ERROR)
		return MLX_ERROR;
	init_hook(&maze);
	mlx_loop(maze.mlx);
}
