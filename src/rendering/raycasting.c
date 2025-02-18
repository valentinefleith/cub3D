/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:51:41 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/12 10:33:07 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

// FOR THE VALID.CUB MAP:
//#define MAP_SQUARE_SIZE 25


static int get_wall_intersection(t_maze *maze, double angle) {
	t_position player_pos = maze->player.pos;
	if (angle < 0)
		angle = (2 * M_PI);
	bool is_facing_up = (angle > M_PI) ? true: false;
	t_position first_intersect;


	printf("angle = %f, facing up = %i\n", angle, is_facing_up);
	if (is_facing_up)
		first_intersect.y = floor(player_pos.y / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE - 1;
	else
		first_intersect.y = floor(player_pos.y / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE + MAP_SQUARE_SIZE;
	first_intersect.x = player_pos.x - (player_pos.y - first_intersect.y) / tan(angle);
	draw_rectangle(maze, first_intersect, 5, 5, RED);
}

static void draw_fov(t_maze *maze) {
	double player_direction = maze->player.looking_angle;
	double first_ray = player_direction - FOV_RADIANS / 2;
	double last_ray = player_direction + FOV_RADIANS / 2;
	printf("ANGLES:\n");
	double current_angle = first_ray;
	while (current_angle < last_ray) {
		int size_til_next_wall = get_wall_intersection(maze, current_angle);
		draw_line_from_angle(maze, maze->player.pos, current_angle, 100, BLUE);
		current_angle += 0.1;
	}
}

void	raycasting(t_maze *maze)
{
	t_position	center_pos;

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
			center_pos.x = center_pos.x + MAP_SQUARE_SIZE;
		}
		center_pos.y = center_pos.y + MAP_SQUARE_SIZE;
	}
	draw_grid(maze);
	draw_rectangle(maze, maze->player.pos, PLAYER_WIDTH_PX, PLAYER_WIDTH_PX,
		GREEN);
	draw_line_from_angle(maze, maze->player.pos, maze->player.looking_angle,
		70, RED);
	draw_fov(maze);
}
