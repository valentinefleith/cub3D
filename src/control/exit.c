/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:30:56 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 21:33:17 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int free_window(t_maze* maze)
{
	if (maze->mlx && maze->win)
		mlx_destroy_window(maze->mlx, maze->win);
	if (maze->mlx)
	{
		mlx_destroy_display(maze->mlx);
		free(maze->mlx);
	}
	return (KO);
}

int	drestroy_textures_img(t_maze *game)
{
	int	i;

	i = 0;
	if (!game || !game->mlx)
		return (KO);
	while (i < 4)
	{
		if (game->texture[i].img)
			mlx_destroy_image(game->mlx, game->texture[i].img);
		i++;
	}
	return (SUCCESS);
}

int exit_program(t_maze *maze, int exit_code)
{
	if (maze)
	{
		if (maze->img.img)
			mlx_destroy_image(maze->mlx, maze->img.img);
		if (maze->minimap.img)
			mlx_destroy_image(maze->mlx, maze->minimap.img);
		drestroy_textures_img(maze);
		free_window(maze);
		free_map(&maze->map);
	}
	if (exit_code != 1 && exit_code != 0)
		exit_code = 0;
	exit(exit_code);
	return (EXIT_FAILURE);
}

