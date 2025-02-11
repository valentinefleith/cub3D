/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:51:41 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/11 21:44:21 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

#define MAP_SQUARE_SIZE 110


void	raycasting(t_maze *maze)
{
	t_position	center_pos;
	t_position	start;
	t_position	end;

	center_pos.y = MAP_SQUARE_SIZE / 2;
	for (int i = 0; i < maze->map->dimensions.height; i++)
	{
		center_pos.x = MAP_SQUARE_SIZE / 2;
		for (int j = 0; j < maze->map->dimensions.width; j++)
		{
			if (maze->map->maze[i][j] == '1')
				draw_rectangle(maze, center_pos, MAP_SQUARE_SIZE,
					MAP_SQUARE_SIZE, WHITE);
			else
				draw_rectangle(maze, center_pos, MAP_SQUARE_SIZE,
					MAP_SQUARE_SIZE, GREY);
			center_pos.x = center_pos.x + MAP_SQUARE_SIZE + 3;
		}
		center_pos.y = center_pos.y + MAP_SQUARE_SIZE + 3;
	}
	draw_rectangle(maze, maze->player.pos, PLAYER_WIDTH_PX, PLAYER_WIDTH_PX,
		GREEN);
	start.x = 100;
	start.y = 200;
	end.x = 480;
	end.y = 495;
	// draw_line(maze, maze->player.pos, end);
	draw_line_from_angle(maze, maze->player.pos, maze->player.looking_angle,
		70);
}
