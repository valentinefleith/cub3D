/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:51:41 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 23:47:31 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

#define MAP_SQUARE_SIZE 110

static void draw_rectangle(t_maze *maze, t_position center_pos, int width, int height, int color) {
	int start_i = center_pos.x - (width / 2);
	int start_j = center_pos.y - (height / 2);

	for (int i = start_i; i < start_i + width; i++) {
		for (int j = start_j; j < start_j + height; j++) {
			my_mlx_pixel_put(&(maze->img), i, j, color);
		}
	}
}

void	raycasting(t_maze *maze)
{
	t_position center_pos;
	center_pos.y = MAP_SQUARE_SIZE / 2;
	for (int i = 0; i < 8; i++) {
	center_pos.x = MAP_SQUARE_SIZE / 2;
		for (int j = 0; j < 8; j++) {
			if (maze->map->maze[i][j] == '1')
				draw_rectangle(maze, center_pos, MAP_SQUARE_SIZE, MAP_SQUARE_SIZE, WHITE);	
			else
				draw_rectangle(maze, center_pos, MAP_SQUARE_SIZE, MAP_SQUARE_SIZE, GREY);	
			center_pos.x = center_pos.x + MAP_SQUARE_SIZE + 3;
		}
		center_pos.y = center_pos.y + MAP_SQUARE_SIZE + 3;
	}

	t_position img_center;
	img_center.x = WIDTH / 2;
	img_center.y = HEIGHT / 2;
	draw_rectangle(maze, maze->player.pos, PLAYER_WIDTH_PX, PLAYER_WIDTH_PX, GREEN);
}
