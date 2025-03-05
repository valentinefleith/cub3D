#include "cub3d.h"
#include "raycasting.h"

void	raycasting(t_maze *maze)
{
	t_vector	wall_point;
	double		current_angle;
	double		distance;
	double		wall_height;
	int			x;

	current_angle = maze->player.looking_angle - (FOV_RADIANS / 2);
	x = 0;
	// if (maze->minimap_key)
	// {
	// 	minimap(maze);
	// 	return ;
	// }
	while (x < WIDTH)
	{
		wall_point = find_wall_point(maze, normalize_angle(current_angle));
		distance = get_wall_distance(maze->player.pos, wall_point, normalize_angle(maze->player.looking_angle), normalize_angle(current_angle));
		wall_height = (TILE_SIZE / distance) * maze->plane_distance; // reminder plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2)
		draw_wall(maze, setup_texture(maze, wall_point, current_angle), wall_height, x);
		// draw_wall(maze, wall_point, wall_height, x);
		current_angle += FOV_RADIANS / (double)WIDTH;
		x++;
	}
}

t_vector	find_wall_point(t_maze *maze, double angle)
{
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	closest_point;
	t_dir 		direction;

	direction = get_horizontal_direction(angle);
	horizontal = get_first_x_point(maze->player.pos, angle, direction);
	horizontal = get_point_horizon(maze->map, angle, direction, horizontal);
	direction = get_vertical_direction(angle);
	vertical = get_first_y_point(maze->player.pos, angle, direction);
	vertical = get_point_vert(maze->map, angle, direction, vertical);
	closest_point = get_closest_point(maze->player.pos, horizontal, vertical, \
		&maze->horizontal_point);
	return (closest_point);
}

bool is_wall_point(t_map *map, t_vector point)
{
	t_point	grid;

	if (!map || !map->maze)
		return (true);
	grid.x = floor(point.x / TILE_SIZE);
	grid.y = floor(point.y / TILE_SIZE);
	if (grid.y < 0 || grid.x >= map->dimensions.width || grid.y > map->dimensions.height || grid.x < 0)
		return (true);
	// if (map->maze[grid.y])
	// 	printf("%s\n", map->maze[grid.y]);
	if (map->maze[grid.y] && map->maze[grid.y][grid.x])
		return (map->maze[grid.y][grid.x] == '1');
	return (false);
}
