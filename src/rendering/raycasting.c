/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:51:41 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 22:26:55 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static bool is_at_players_pos(t_maze *maze, int i, int j) {
	return i >= maze->player.pos.x - PLAYER_WIDTH_PX && i <= maze->player.pos.x + PLAYER_WIDTH_PX && j >= maze->player.pos.y - PLAYER_WIDTH_PX && j <= maze->player.pos.y + PLAYER_WIDTH_PX;
}

void raycasting(t_maze *maze) {
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (is_at_players_pos(maze, i, j))
				my_mlx_pixel_put(&(maze->img), i, j, GREEN);
			else
				my_mlx_pixel_put(&(maze->img), i, j, GREY);
		}
	}
}
