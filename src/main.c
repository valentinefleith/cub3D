/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:18:47 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 22:03:44 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_maze maze;
	t_map map;

	if (init_map(ac, av[1], &map) != SUCCESS)
		return (KO);
	maze.map = &map;
	maze.mlx = mlx_init();
	if (!maze.mlx)
		return MLX_ERROR;
	maze.win = mlx_new_window(maze.mlx, WIDTH, HEIGHT, "cub3D");
	if (!maze.win) {
		mlx_destroy_display(maze.mlx);
		free(maze.mlx);
		return MLX_ERROR;
	}
	init_player_pos(&maze);
	maze.plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2);
	if (render_one_frame(&maze, true) == MLX_ERROR)
		return MLX_ERROR;
	init_hook(&maze);
	mlx_loop(maze.mlx);
	free_map(&map);
}
