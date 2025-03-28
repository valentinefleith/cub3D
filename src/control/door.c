/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:55:29 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 15:56:04 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	get_facing_wall_pos(char **maze, t_point grid, double view_dir)
{
	t_point	facing_wall;

	facing_wall.x = grid.x;
	facing_wall.y = grid.y;
	if (get_horizontal_direction(view_dir) == facing_down)
		facing_wall.y += 1;
	else
		facing_wall.y -= 1;
	if (maze[facing_wall.y][facing_wall.x] == '1'
		|| maze[facing_wall.y][facing_wall.x] == '0')
	{
		facing_wall.y = grid.y;
		if (get_vertical_direction(view_dir) == facing_left)
			facing_wall.x -= 1;
		else
			facing_wall.x += 1;
	}
	return (facing_wall);
}

int	puzzle_game(t_maze *game, char **maze)
{
	t_point	grid;

	if (!game || !maze)
		return (KO);
	grid.x = game->player.pos.x / TILE_SIZE;
	grid.y = game->player.pos.y / TILE_SIZE;
	grid = get_facing_wall_pos(maze, grid, game->player.looking_angle);
	if (maze[grid.y] && maze[grid.y][grid.x])
	{
		if (maze[grid.y][grid.x] == '2')
			return (handle_door(game, &game->map, grid));
		if (maze[grid.y][grid.x] >= '3' && maze[grid.y][grid.x] <= '5')
			return (handle_sequence_color(game, maze[grid.y][grid.x]));
	}
	return (SUCCESS);
}

int	handle_sequence_color(t_maze *game, char wall_type)
{
	if (wall_type == '3')
		game->map.color_picked = game->map.color_sequence[0];
	else if (wall_type == '4')
		game->map.color_picked = game->map.color_sequence[1];
	else if (wall_type == '5')
		game->map.color_picked = game->map.color_sequence[2];
	return (SUCCESS);
}

int	handle_door(t_maze *game, t_map *map, t_point pos)
{
	static int		i = 0;

	if (map->color_picked == map->color_sequence[i])
	{
		map->color_sequence[i] = -1;
		map->color_picked = -1;
		i++;
	}
	if (i == 3)
	{
		game->map.maze[pos.y][pos.x] = '0';
		printf("Bravo you solved the color puzzle and unlocked the door!\n");
		return (render_one_frame(game, false));
	}
	return (SUCCESS);
}

int	draw_picked_color(t_maze *game)
{
	t_point	pos;

	pos.x = WIDTH / 2;
	pos.y = HEIGHT / 2;
	draw_rectangle(game, pos,
		to_rectangle_characteristics(50, 50, game->map.color_picked));
	return (SUCCESS);
}
