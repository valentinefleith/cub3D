#include "cub3d.h"

void draw_grid(t_maze *maze)
{
	t_point	start;
	t_point	end;

	start.x = 1;
	start.y = 1;
	end.x = 1;
	end.y = (maze->map.height * MINI_TILE + MINI_TILE / 4) - 2;
	while (start.x <  maze->map.width * MINI_TILE + MINI_TILE)
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
			if (game->map.maze[i][j] == '1')
				draw_rectangle(game, pos, MINI_TILE, MINI_TILE, game->map.floor_color);
			else
				draw_rectangle(game, pos, MINI_TILE, MINI_TILE, GREY);
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
	// printf("player pos x: %f\n", game->player.pos.x);
	// printf("player pos y: %f\n", game->player.pos.y);
	player.x = game->player.pos.x / TILE_SIZE * MINI_TILE;
	player.y = game->player.pos.y / TILE_SIZE * MINI_TILE;
	// player.x += (MINI_TILE / 2);
	// player.y += (MINI_TILE / 2);
	draw_rectangle(game, player, PLAYER_RADIUS, PLAYER_RADIUS, PINK);
}

// int	minimap(t_maze *game)
// {
// 	if (!game)
// 		return (KO);
// 	if (game->minimap_key)
// 	{
// 		draw_minimap(game);
// 		draw_player(game);
// 	}
// 	return (SUCCESS);
// }

void	draw_rectangle(t_maze *maze, t_point center_pos, int width,
		int height, int color)
{
	int	start_i;
	int	start_j;

	start_i = center_pos.x - (width / 2);
	start_j = center_pos.y - (height / 2);
	for (int i = start_i; i < start_i + width; i++)
	{
		for (int j = start_j; j < start_j + height; j++)
			my_mlx_pixel_put(&(maze->img), i, j, color);
	}
}

void	draw_line(t_maze *maze, t_point start, t_point end, int color)
{
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	error;
	int	error2;

	delta_x = abs(end.x - start.x);
	delta_y = abs(end.y - start.y);
	if (start.x < end.x)
		step_x = 1;
	else
		step_x = -1;
	if (start.y < end.y)
		step_y = 1;
	else
		step_y = -1;
	error = delta_x - delta_y;
	while (start.x != end.x || start.y != end.y)
	{
		my_mlx_pixel_put(&(maze->img), start.x, start.y, color);
		error2 = 2 * error;
		if (error2 > -delta_y)
		{
			error -= delta_y;
			start.x += step_x;
		}
		if (error2 < delta_x)
		{
			error += delta_x;
			start.y += step_y;
		}
	}
}

void	draw_line_from_angle(t_maze *maze, t_vector point, double angle,
		double size, int color)
{
	t_point	endpoint;
	t_point	player;

	player.x = floor(point.x / TILE_SIZE) * (MINI_TILE + MINI_TILE) / 2;
	player.y = floor(point.y / TILE_SIZE) * (MINI_TILE + MINI_TILE) / 2;
	player.x += (MINI_TILE / 2);
	player.y += (MINI_TILE / 2);
	endpoint.y = player.y + (size * sin(angle));
	endpoint.x = player.x + (size * cos(angle));
	if (player.y < 0 || player.x > WIDTH || player.x < 0 || player.y > HEIGHT || endpoint.y < 0 || endpoint.y > HEIGHT)
		return ;
	draw_line(maze, player, endpoint, color);
}
