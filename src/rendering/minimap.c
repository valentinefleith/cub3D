#include "cub3d.h"

// int	parsing_minimap(t_maze *game, t_minimap *minimap)
// {
// 	t_map		*map;

// 	map = game->map;
// 	minimap->width = map->dimensions.width / 4;
// 	minimap->height = map->dimensions.height / 4;
// 	if (minimap->width < 0)
// 		minimap->width = 100;
// 	if (minimap->height < 0)
// 		minimap->height = 50;
// 	minimap->cell_size = TILE_SIZE / 4;
// }

// int	render_minimap(t_maze *game)
// {
// 	draw_grid(game);
// }

int	minimap(t_maze *game)
{
	t_img	minimap;

	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
	minimap.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!minimap.img)
		return (exit_program(game), KO);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bits_per_pixel, \
		&minimap.line_length, &minimap.endian);
	game->minimap = minimap;
	// render_minimap(game);
	draw_fov(game);
	mlx_put_image_to_window(game->mlx, game->win, minimap.img, 0, 0);
	return (SUCCESS);
}

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
		{
			my_mlx_pixel_put(&(maze->minimap), i, j, color);
		}
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
		my_mlx_pixel_put(&(maze->minimap), start.x, start.y, color);
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

void	draw_line_from_angle(t_maze *maze, t_point point, double angle,
		int size, int color)
{
	t_point	endpoint;

	endpoint.y = point.y + (int)(size * sin(angle));
	endpoint.x = point.x + (int)(size * cos(angle));
	if (point.y < 0 || point.x > WIDTH || point.x < 0 || point.y > HEIGHT || endpoint.y < 0 || endpoint.y > HEIGHT)
		return ;
	draw_line(maze, point, endpoint, color);
}

void draw_grid(t_maze *maze)
{
	t_point	start;
	t_point	end;

	start.x = 0;
	start.y = 0;
	end.x = 0;
	end.y = MINI_HEIGHT;
	while (start.x <= MINI_WIDTH)
	{
		draw_line(maze, start, end, BLACK);
		start.x += MINI_TILE;
		end.x += MINI_TILE;
	}
	start.x = 0;
	start.y = 0;
	end.x = MINI_WIDTH;
	end.y = 0;
	while (start.y <= MINI_HEIGHT)
	{
		draw_line(maze, start, end, BLACK);
		start.y += MINI_TILE;
		end.y += MINI_TILE;
	}
}

void	draw_fov(t_maze *game)
{
	t_point	center_pos;
	t_point	player;
	int		i;
	int		j;

	i = 0;
	center_pos.y = MINI_TILE / 2; 
	while (i < game->map->dimensions.height)
	{
		center_pos.x = MINI_TILE / 2;
		j = 0;
		while (j < game->map->dimensions.width)
		{
			if (game->map->maze[i][j] == '1')
				draw_rectangle(game, center_pos, MINI_TILE, MINI_TILE, WHITE);
			else
				draw_rectangle(game, center_pos, MINI_TILE, MINI_TILE, GREY);
			center_pos.x += MINI_TILE;
			j++;
		}
		center_pos.y += MINI_TILE;
		i++;
	}
	draw_grid(game);
	player.x = floor(game->player.pos.x);
	player.y = floor(game->player.pos.y);
	draw_rectangle(game, player, 3, 3, GREEN);
}

// void	draw_fov(t_maze *maze)
// {
// 	t_point	center_pos;

// 	center_pos.y = MINI_TILE / 2;
// 	for (int i = 0; i < maze->map->dimensions.height; i++)
// 	{
// 		center_pos.x = MINI_TILE / 2;
// 		for (int j = 0; j < maze->map->dimensions.width; j++)
// 		{
// 			if (maze->map->maze[i][j] == '1')
// 				draw_rectangle(maze, center_pos, MINI_TILE,
// 					MINI_TILE, WHITE);
// 			else
// 				draw_rectangle(maze, center_pos, MINI_TILE,
// 					MINI_TILE, GREY);
// 			center_pos.x = center_pos.x + MINI_TILE;
// 		}
// 		center_pos.y = center_pos.y + MINI_TILE;
// 	}
// 	draw_grid(maze);
// 	draw_rectangle(maze, maze->player.pos, PLAYER_WIDTH_PX, PLAYER_WIDTH_PX,
// 		GREEN);
// 	draw_line_from_angle(maze, maze->player.pos, maze->player.looking_angle,
// 		70, RED);
// 	// raycasting(maze);
// }