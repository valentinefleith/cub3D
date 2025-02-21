/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:17:35 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/11 21:34:15 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	update_maze_coordinates(t_maze *maze, double x_angle, double y_angle, t_position player_pos)
{
	t_position	grid;
	t_position	new_pos;

	if (!maze)
		return (KO);
	new_pos.x = roundf((x_angle * PLAYER_SPEED) + player_pos.x);
	new_pos.y = roundf((y_angle * PLAYER_SPEED) + player_pos.y);
	grid.x = (new_pos.x / TILE_SIZE);
	grid.y = (new_pos.y / TILE_SIZE);
	// printf("x = %d / y = %d\n", grid.x, grid.y);
	// if (maze->map->maze[grid.y] && maze->map->maze[grid.y][grid.x])
	// 	printf("%s", maze->map->maze[grid.y]);
	if (maze->map->maze[grid.y] && maze->map->maze[grid.y][grid.x] != '1')
		maze->player.pos = new_pos;
	else
		return (KO);
	return (SUCCESS);
}

static int move_player(t_maze *maze, int keycode, double angle)
{
	if (keycode == XK_d)
		update_maze_coordinates(maze, -sin(angle), cos(angle), maze->player.pos);
	else if (keycode == XK_a)
		update_maze_coordinates(maze, sin(angle), -cos(angle), maze->player.pos);
	else if (keycode == XK_w)
		update_maze_coordinates(maze, cos(angle), sin(angle), maze->player.pos);
	else if (keycode == XK_s)
		update_maze_coordinates(maze, -cos(angle), -sin(angle), maze->player.pos);
	// if (keycode == XK_d)
	// 	maze->player.pos.x += PLAYER_MOVE_PX;
	// else if (keycode == XK_a)
	// 	maze->player.pos.x -= PLAYER_MOVE_PX;
	// else if (keycode == XK_w)
	// 	maze->player.pos.y -= PLAYER_MOVE_PX;
	// else if (keycode == XK_s)
	// 	maze->player.pos.y += PLAYER_MOVE_PX;
	render_one_frame(maze, false);
	return (SUCCESS);
}

static int rotate_player(t_maze *maze, int keycode)
{
	// if (keycode == XK_Left)
	// 	maze->player.looking_angle = fmod(maze->player.looking_angle + 0.1, 2 * M_PI) ;
	// else
	// 	maze->player.looking_angle -= 0.1;
	if (keycode == XK_Left)
	{
		maze->player.looking_angle += ROTATION_SPEED;
		if (maze->player.looking_angle > 2 * M_PI)
			maze->player.looking_angle -= 2 * M_PI;
	}
	else
	{
		maze->player.looking_angle -= ROTATION_SPEED;
		if (maze->player.looking_angle < 0)
			maze->player.looking_angle += 2 * M_PI;
	}
	render_one_frame(maze, false);
	return SUCCESS;
}

int key_events(int keycode, t_maze *maze)
{
	if (keycode == XK_s || keycode == XK_w || keycode == XK_a || keycode == XK_d)
		return (move_player(maze, keycode, maze->player.looking_angle));
	if (keycode == XK_Right || keycode == XK_Left)
		return (rotate_player(maze, keycode));
	return 0;
}
