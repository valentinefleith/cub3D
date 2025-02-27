#include "cub3d.h"
#include "raycasting.h"

void	raycasting(t_maze *maze)
{
	t_vector	wall_point;
	double		current_angle;
	double		distance;
	int			wall_height;
	int			x;
	
	current_angle = maze->player.looking_angle - (FOV_RADIANS / 2);
	x = 0;
	while (x < WIDTH)
	{
		wall_point = find_wall_point(maze, normalize_angle(current_angle));
		distance = get_wall_distance(maze->player.pos, wall_point, normalize_angle(maze->player.looking_angle), normalize_angle(current_angle));
		if (distance < 0.1)
			distance = 0.1;
		wall_height = (TILE_SIZE / distance) * maze->plane_distance; // reminder plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2)
		draw_wall(maze, wall_point, wall_height, x);
		current_angle += FOV_RADIANS / WIDTH;
		x++;
	}
}

t_vector	find_wall_point(t_maze *maze, double angle)
{
	t_vector	horizontal_point;
	t_vector	vertical_point;
	t_vector	closest_point;
	t_dir 		direction;

	direction = get_horizontal_direction(angle);
	horizontal_point = get_first_x_point(maze->player.pos, angle, direction);
	horizontal_point = get_wall_point_horizon(maze->map, angle, direction, horizontal_point);
	direction = get_vertical_direction(angle);
	vertical_point = get_first_y_point(maze->player.pos, angle, direction);
	vertical_point = get_wall_point_vert(maze->map, angle, direction, vertical_point);
	closest_point = get_closest_point(maze->player.pos, horizontal_point, vertical_point, &maze->texture.orientation);
	return (closest_point);
}

bool is_wall_point(t_map *map, t_vector point)
{
	t_point	grid;

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
