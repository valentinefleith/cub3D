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
	mlx_destroy_window(maze->mlx, maze->win);
	mlx_destroy_display(maze->mlx);
	free(maze->mlx);
	return 0;
}

int exit_program(t_maze *maze)
{
	mlx_destroy_image(maze->mlx, maze->img.img);
	mlx_destroy_image(maze->mlx, maze->texture.img);
	free_window(maze);
	free_map(maze->map);
	exit(0);
	return SUCCESS;
}

