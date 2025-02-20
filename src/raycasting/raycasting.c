#include "cub3d.h"
#include "raycasting.h"

void	raycasting(t_maze *maze)
{
	t_position	center_pos;

	center_pos.y = TILE_SIZE / 2;
	for (int i = 0; i < maze->map->dimensions.height; i++)
	{
		center_pos.x = TILE_SIZE / 2;
		for (int j = 0; j < maze->map->dimensions.width; j++)
		{
			if (maze->map->maze[i][j] == '1')
				draw_rectangle(maze, center_pos, TILE_SIZE,
					TILE_SIZE, WHITE);
			else
				draw_rectangle(maze, center_pos, TILE_SIZE,
					TILE_SIZE, GREY);
			center_pos.x = center_pos.x + TILE_SIZE;
		}
		center_pos.y = center_pos.y + TILE_SIZE;
	}
	draw_grid(maze);
	draw_rectangle(maze, maze->player.pos, PLAYER_WIDTH_PX, PLAYER_WIDTH_PX,
		GREEN);
	draw_line_from_angle(maze, maze->player.pos, maze->player.looking_angle,
		70, RED);
	draw_fov(maze);
}

int	find_wall_distance(t_maze *maze, double angle)
{
	t_position	vertical_wall;
	t_position	horizontal_wall;
	t_position	vertical_first;
	t_position	horizontal_first;
	t_dir 		direction;
	int			distance;


	direction = get_horizontal_direction(angle);
	horizontal_first = get_first_x_point(maze->player.pos, angle, direction);
	horizontal_wall = get_wall_point_horizon(maze, maze->map, angle, direction, horizontal_first);
	direction = get_vertical_direction(angle);
	vertical_first = get_first_y_point(maze->player.pos, angle, direction);
	vertical_wall = get_wall_point_vert(maze, maze->map, angle, direction, vertical_first);
	distance = get_smallest_distance(maze->player.pos, horizontal_wall, vertical_wall);
	return (distance);
}

bool is_wall_point(t_map *map, t_position point)
{
	t_position	grid;

	if (!map)
		return (false);
	grid.x = floor(point.x / TILE_SIZE);
	grid.y = floor(point.y / TILE_SIZE);
	// printf("\ngrid.x = %d // grid.y = %d \n", grid.x, grid.y);
	if (grid.y < 0 || grid.x >= map->dimensions.width || grid.y > map->dimensions.height || grid.x < 0)
		return (true);
	if (map->maze[grid.y] && map->maze[grid.y][grid.x])
		return (map->maze[grid.y][grid.x] == '1');
	return (false);
}

int	compute_distance(t_position a, t_position b)
{
	int	norm;

	t_position vector;
	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	norm = sqrt(vector.x * vector.x + vector.y * vector.y);

	return (norm);
}

int	get_smallest_distance(t_position target, t_position a, t_position b)
{
	int distance_1;
	int distance_2;

	distance_1 = compute_distance(target, a);
	distance_2 = compute_distance(target, b);
	return (fmin(distance_1, distance_2));
}