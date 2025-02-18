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
	t_maze		game;
	t_raycast	rc;
	t_map		map;

	if (init_map(ac, av[1], &map) != SUCCESS)
		return (KO);
	game.map = &map;
	game.mlx = mlx_init();
	if (!game.mlx)
		return MLX_ERROR;
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	if (!game.win) {
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		return MLX_ERROR;
	}
	rc = init_raycasting();
	game.rc = &rc;
	if (render_one_frame(&game, true) == MLX_ERROR)
		return MLX_ERROR;
	init_hook(&game);
	mlx_loop(game.mlx);
	free_map(&map);
}
