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
	t_map	map;

	/* Parsing necessary data */
	if (init_map(ac, av[1], &map) != SUCCESS)
		return (KO);
	game.map = &map;

	/* Init game data */
	game.mlx = NULL;
	game.mlx = mlx_init();
	if (!game.mlx)
		return MLX_ERROR;
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	if (!game.win) {
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		return MLX_ERROR;
	}
	game.img = init_img_struct();
	game.minimap.img = NULL;
	game.minimap_key = false;
	if (!init_textures(&game))
		exit_program(&game);
	init_player_pos(&game);
	game.plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2.0);
	/* Launch game and mlx loop */
	game_loop(&game);

	/* Destroy mlx and clean program, then exit */
	free_map(&map);
}
