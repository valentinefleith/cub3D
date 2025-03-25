#include "cub3d.h"
#include "raycasting.h"
#define DISTANCE_MINIMAP 40

void	raycasting(t_maze *maze)
{
	t_vector	wall_point;
	double		current_angle;
	double		distance;
	double		wall_height;
	int			x;

	current_angle = maze->player.looking_angle - (FOV_RADIANS / 2.0);
	x = 0;
	while (x < WIDTH)
	{
		current_angle = normalize_angle(current_angle);
		wall_point = find_wall_point(maze, current_angle);
		distance = get_wall_distance(maze->player.pos, wall_point, normalize_angle(maze->player.looking_angle), current_angle);
		wall_height = ((double)TILE_SIZE / distance) * maze->plane_distance; // reminder plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2)
		draw_wall(maze, setup_texture(maze, wall_point, current_angle), wall_height, x);
		current_angle += (FOV_RADIANS / (double)WIDTH);
		x++;
	}
	if (maze->minimap_key)
	{
		draw_minimap(maze);
		draw_line_from_angle(maze, maze->player.pos, maze->player.looking_angle - (FOV_RADIANS / 2.0), DISTANCE_MINIMAP, WHITE);
		draw_line_from_angle(maze, maze->player.pos, current_angle, DISTANCE_MINIMAP, WHITE);
	}
}

static int	get_wall_type(t_vector point, char **maze)
{
	t_point	grid;

	if (!maze)
		return (-1);
	grid.x = floor(point.x / TILE_SIZE);
	grid.y = floor(point.y / TILE_SIZE);
	if (maze[grid.y] && maze[grid.y][grid.x])
	{
		if (maze[grid.y][grid.x] == '1')
			return (1);
		else if (maze[grid.y][grid.x] == '2')
			return (2);
		else if (maze[grid.y][grid.x] == '3')
			return (3);
		else if (maze[grid.y][grid.x] == '4')
			return (4);
		else if (maze[grid.y][grid.x] == '5')
			return (5);
	}
	return (-1);
}

t_vector	find_wall_point(t_maze *maze, double angle)
{
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	closest_point;
	t_dir 		direction;

	direction = get_horizontal_direction(angle);
	horizontal = get_first_x_point(maze->player.pos, angle, direction);
	horizontal = get_point_horizon(&(maze->map), angle, direction, horizontal);
	direction = get_vertical_direction(angle);
	vertical = get_first_y_point(maze->player.pos, angle, direction);
	vertical = get_point_vert(&(maze->map), angle, direction, vertical);
	closest_point = get_closest_point(maze->player.pos, horizontal, vertical, \
		&maze->horizontal_point);
	maze->wall_type = get_wall_type(closest_point, maze->map.maze);
	return (closest_point);
}

bool is_wall_point(t_map *map, t_vector point)
{
	t_point	grid;

	if (!map || !map->maze)
		return (true);
	grid.x = floor(point.x / TILE_SIZE);
	grid.y = floor(point.y / TILE_SIZE);
	if (grid.y < 0 || grid.x >= map->width || grid.y >= map->height || grid.x < 0)
		return (true);
	if (map->maze[grid.y] && map->maze[grid.y][grid.x])
	{
		if (map->maze[grid.y][grid.x] == '1'
			|| map->maze[grid.y][grid.x] == '2'
			|| map->maze[grid.y][grid.x] == '3'
			|| map->maze[grid.y][grid.x] == '4'
			|| map->maze[grid.y][grid.x] == '5')
			return (true);
	}
	return (false);
}
