/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:18:47 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 21:50:17 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
	if (render_one_frame(&maze, true) == MLX_ERROR)
		return MLX_ERROR;
	init_hook(&maze);
	mlx_loop(maze.mlx);
}
