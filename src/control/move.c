/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:00:50 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 16:02:09 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// player_radius defines a min distance between the wall and the player
// and ensures that even while moving diagonally we can detect a wall
static int	detect_wall_collision(char **maze, t_vector new_pos, char x, char y)
{
	t_point	grid;

	if (x == '+')
		grid.x = floor((new_pos.x + PLAYER_RADIUS) / TILE_SIZE);
	else
		grid.x = floor((new_pos.x - PLAYER_RADIUS) / TILE_SIZE);
	if (y == '+')
		grid.y = floor((new_pos.y + PLAYER_RADIUS) / TILE_SIZE);
	else
		grid.y = floor((new_pos.y - PLAYER_RADIUS) / TILE_SIZE);
	if (maze && maze[grid.y] && (maze[grid.y][grid.x] == '1'
		|| maze[grid.y][grid.x] == '2' || maze[grid.y][grid.x] == '3'
		|| maze[grid.y][grid.x] == '4' || maze[grid.y][grid.x] == '5'))
		return (KO);
	return (SUCCESS);
}

int	update_position(t_maze *game, double x_angle, double y_angle, \
	t_vector player_pos)
{
	t_vector	new_pos;

	if (!game || !game->map.maze)
		return (KO);
	new_pos.x = ((x_angle * PLAYER_SPEED) + player_pos.x);
	new_pos.y = ((y_angle * PLAYER_SPEED) + player_pos.y);
	if (!detect_wall_collision(game->map.maze, new_pos, '-', '-'))
		return (KO);
	if (!detect_wall_collision(game->map.maze, new_pos, '+', '-'))
		return (KO);
	if (!detect_wall_collision(game->map.maze, new_pos, '-', '+'))
		return (KO);
	if (!detect_wall_collision(game->map.maze, new_pos, '+', '+'))
		return (KO);
	game->player.pos = new_pos;
	render_one_frame(game, false);
	return (SUCCESS);
}

static int	move_player(t_maze *game, double angle, int key_pressed)
{
	double	sine;
	double	cosine;

	sine = sin(angle);
	cosine = cos(angle);
	if (key_pressed == right)
		return (update_position(game, -sine, cosine, game->player.pos));
	else if (key_pressed == left)
		return (update_position(game, sine, -cosine, game->player.pos));
	else if (key_pressed == front)
		return (update_position(game, cosine, sine, game->player.pos));
	else if (key_pressed == back)
		return (update_position(game, -cosine, -sine, game->player.pos));
	return (KO);
}

int	rotate_player(t_maze *game, int key_pressed)
{
	if (key_pressed == right_rotation)
	{
		game->player.looking_angle += ROTATION_SPEED;
		if (game->player.looking_angle > 2.0 * M_PI)
			game->player.looking_angle -= 2.0 * M_PI;
		return (render_one_frame(game, false));
	}
	else if (key_pressed == left_rotation)
	{
		game->player.looking_angle -= ROTATION_SPEED;
		if (game->player.looking_angle < 0)
			game->player.looking_angle += 2.0 * M_PI;
		return (render_one_frame(game, false));
	}
	return (KO);
}

int	update_player_pos(t_maze *game)
{
	if (game->player.keys_pressed[front])
		move_player(game, game->player.looking_angle, front);
	if (game->player.keys_pressed[back])
		move_player(game, game->player.looking_angle, back);
	if (game->player.keys_pressed[left])
		move_player(game, game->player.looking_angle, left);
	if (game->player.keys_pressed[right])
		move_player(game, game->player.looking_angle, right);
	if (game->player.keys_pressed[right_rotation])
		rotate_player(game, right_rotation);
	if (game->player.keys_pressed[left_rotation])
		rotate_player(game, left_rotation);
	if (game->minimap_key || !game->minimap_key)
		render_one_frame(game, false);
	if (game->player.keys_pressed[shift])
		puzzle_game(game, game->map.maze);
	return (SUCCESS);
}
