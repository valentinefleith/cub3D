/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:51:41 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/18 19:59:47 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

// FOR THE VALID.CUB MAP:
//#define MAP_SQUARE_SIZE 25

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return (angle);
}

static t_position get_first_intersect_x(t_position player_pos, double angle, bool is_facing_up)
{
	t_position	first_intersect;

	if (is_facing_up)
		first_intersect.y = floor(player_pos.y / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE - 1;
	else
		first_intersect.y = floor(player_pos.y / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE + MAP_SQUARE_SIZE;
	first_intersect.x = player_pos.x - (player_pos.y - first_intersect.y) / tan(angle);
	return (first_intersect);
}

static t_position get_first_intersect_y(t_position player_pos, double angle, bool is_facing_up)
{
	t_position	first_intersect;

	if (!is_facing_up)
		first_intersect.x = floor(player_pos.x / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE - 1;
	else
		first_intersect.x = floor(player_pos.x / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE + MAP_SQUARE_SIZE;
	if (angle > M_PI && angle < 2 * M_PI)
		first_intersect.y = player_pos.y - (player_pos.x - first_intersect.x) * tan(angle);
	else
		first_intersect.y = player_pos.y + (player_pos.x - first_intersect.x) * tan(angle);
	// printf("INTER_Y.x = %i, INTER_Y.y = %i ANGLE -> %f\n", first_intersect.x, first_intersect.y, angle);
	return (first_intersect);
}

static	t_position get_next_intersection(t_maze *maze, t_position px_pos, double angle)
{
	t_position	horizontal_section;
	t_position	vertical_section;
	bool		is_facing_up;

	angle = normalize_angle(angle);
	is_facing_up = (angle > M_PI && angle < 2 * M_PI) ? true: false;
	horizontal_section = get_first_intersect_x(px_pos, angle, is_facing_up);
	vertical_section = get_first_intersect_y(px_pos, angle, is_facing_up);
		draw_rectangle(maze, horizontal_section, 5, 5, RED);
	// if (vertical_section.y < HEIGHT && vertical_section.x < WIDTH && vertical_section.y > 0)
	// 	draw_rectangle(maze, vertical_section, 5, 5, BLUE);
	return (horizontal_section);
}

static int find_y_angle(double angle)
{
	if (angle > M_PI && angle < 2 * M_PI) // si le rayon va vers le haut
		return (MAP_SQUARE_SIZE);
	else
		return (-MAP_SQUARE_SIZE);
}

static int find_wall_distance(t_maze *maze, double angle)
{
	int			distance;
	int			x_step; // Xa
	int			y_step; // Ya
	t_position	intersection;
	t_position	grid_pos;
	
	distance = 0;
	grid_pos.x = floor(maze->player.pos.x / MAP_SQUARE_SIZE);
	grid_pos.y = floor(maze->player.pos.y / MAP_SQUARE_SIZE);
	intersection.x = maze->player.pos.x;
	intersection.y = maze->player.pos.y;
	// printf("grid->(x=%i, y=%i) // pixel->(x=%i, y=%i) -> angle = %f\n", grid_pos.x, grid_pos.y, intersection.x, intersection.y, angle);
	// while (maze->map->maze[grid_pos.x][grid_pos.y] != '1')
	// {
		intersection = get_next_intersection(maze, intersection, angle);
		grid_pos.x = floor(intersection.x / MAP_SQUARE_SIZE);
		grid_pos.y = floor(intersection.y / MAP_SQUARE_SIZE);
		// if (maze->map->maze[grid_pos.x][grid_pos.y] != '1')
		// 	break ;
		angle = normalize_angle(angle);
		y_step = find_y_angle(angle);
		x_step = MAP_SQUARE_SIZE / tan(angle);
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2) // si le rayon va vers la gauche
			x_step = x_step;
		else
			x_step = -x_step;
		// printf("X angle = %f, Y angle = %f\n", x_step, y_step);
		intersection.x = intersection.x - x_step;
		intersection.y = intersection.y - y_step;
		draw_rectangle(maze, intersection, 5, 5, BLUE);
		// if (vertical_section.y < HEIGHT && vertical_section.x < WIDTH && vertical_section.y > 0)
		// 	draw_rectangle(maze, vertical_section, 5, 5, BLUE);
		// grid_pos.x = (int)intersection.x / MAP_SQUARE_SIZE;
		// grid_pos.y = (int)intersection.y / MAP_SQUARE_SIZE;
		// printf("grid->(x=%i, y=%i) // pixel->(x=%i, y=%i)\n", grid_pos.x, grid_pos.y, intersection.x, intersection.y);
	// }
	return (distance);
}



static void draw_fov(t_maze *maze)
{
	double player_direction = maze->player.looking_angle;
	double first_ray = player_direction - FOV_RADIANS / 2;
	double last_ray = player_direction + FOV_RADIANS / 2;
	double current_angle = first_ray;
	// while (current_angle < last_ray) {
		int size_til_next_wall = find_wall_distance(maze, current_angle);
		draw_line_from_angle(maze, maze->player.pos, current_angle, 400, BLUE);
	// 	current_angle += 0.1;
	// }
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
