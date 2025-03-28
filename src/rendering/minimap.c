/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:24:19 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 18:26:00 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(t_maze *maze)
{
	t_point	start;
	t_point	end;

	start.x = 1;
	start.y = 1;
	end.x = 1;
	end.y = (maze->map.height * MINI_TILE + MINI_TILE / 4) - 2;
	while (start.x < maze->map.width * MINI_TILE + MINI_TILE)
	{
		draw_line(maze, start, end, BLACK);
		start.x += MINI_TILE;
		end.x += MINI_TILE;
	}
	start.x = 1;
	start.y = 1;
	end.x = (maze->map.width * MINI_TILE + MINI_TILE / 4) - 2;
	end.y = 1;
	while (start.y <= maze->map.height * MINI_TILE + MINI_TILE)
	{
		draw_line(maze, start, end, BLACK);
		start.y += MINI_TILE;
		end.y += MINI_TILE;
	}
}

static void	draw_mini_fov(t_maze *game, t_point player_pos)
{
	double	current_angle;
	double	last_ray_angle;

	current_angle = game->player.looking_angle - (FOV_RADIANS / 2.0);
	last_ray_angle = game->player.looking_angle + (FOV_RADIANS / 2.0);
	while (current_angle < last_ray_angle)
	{
		draw_line_from_angle(game, player_pos,
			to_line_characteristics(current_angle, FOV_SIZE, BLUE));
		current_angle += (FOV_RADIANS / (double)WIDTH);
	}
}

static int	get_minimap_color(t_maze *game, int x, int y)
{
	char	minimap_code;

	minimap_code = game->map.maze[x][y];
	if (minimap_code == '2')
		return (game->map.ceilling_color);
	if (minimap_code >= '1' && minimap_code <= '5')
		return (game->map.floor_color);
	return (GREY);
}

void	draw_minimap(t_maze *game)
{
	t_point	pos;
	int		i;
	int		j;

	i = 0;
	pos.y = (MINI_TILE / 2) + 1;
	while (game->map.maze[i])
	{
		pos.x = (MINI_TILE / 2) + 1;
		j = 0;
		while (game->map.maze[i][j])
		{
			draw_rectangle(game, pos, to_rectangle_characteristics(MINI_TILE,
					MINI_TILE, get_minimap_color(game, i, j)));
			pos.x += MINI_TILE;
			j++;
		}
		pos.y += MINI_TILE;
		i++;
	}
	draw_grid(game);
	draw_player(game);
}

void	draw_player(t_maze *game)
{
	t_point	player;

	player.x = game->player.pos.x / TILE_SIZE * MINI_TILE;
	player.y = game->player.pos.y / TILE_SIZE * MINI_TILE;
	draw_mini_fov(game, player);
	draw_rectangle(game, player, to_rectangle_characteristics(PLAYER_RADIUS,
			PLAYER_RADIUS, PINK));
}
