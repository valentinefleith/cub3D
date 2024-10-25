/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:18:47 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/25 10:41:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_window(t_maze *maze)
{
	mlx_destroy_window(maze->mlx, maze->win);
	mlx_destroy_display(maze->mlx);
	free(maze->mlx);
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
	mlx_put_image_to_window(maze->mlx, maze->win, img.img, 0, 0);
	return SUCCESS;
}

int main() {
	t_maze maze;

	printf("coucou\n");
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

}
