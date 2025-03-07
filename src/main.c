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

// hook for key press
	// hook for key realese
// loop hook for update player position
int	game_loop(t_maze *game)
{
	if (render_one_frame(game, true) == MLX_ERROR)
		return (MLX_ERROR);
	mlx_hook(game->win, 17, 0, exit_program, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_loop_hook(game->mlx, &update_player_pos, game);
	// mlx_loop_hook(game->mlx, &minimap, game);
	mlx_loop(game->mlx);
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_maze	game;

	game = game_initialization();
	if (!parsing_map_file(ac, av[1], &game.map, &game.player))
		return (free_map(&game.map), EXIT_FAILURE);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (exit_program(&game, EXIT_FAILURE));
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	if (!game.win)
		return (exit_program(&game, EXIT_FAILURE));
	init_textures(&game);
	game_loop(&game);
	return (exit_program(&game, 0));
}
