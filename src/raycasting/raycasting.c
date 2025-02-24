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
		// distance = find_wall_distance(maze, normalize_angle(current_angle));
		wall_point = find_wall_distance(maze, normalize_angle(current_angle));
		distance = find_wall_distance(wall_point);
		distance = distance * cos(current_angle - maze->player.looking_angle); // correct fish-eye
		wall_height = (TILE_SIZE / distance) * maze->plane_distance; // reminder plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2)
		if (*(maze->img.orientation) == 1)
			maze->img.x = get_x_bitmap(maze->img, wall_point.x);
		// printf("dist = %d // height = %d // angle = %f\n", distance, wall_height, current_angle);
		draw_wall(maze, wall_height, x);
		// draw_line_from_angle(maze, maze->player.pos, current_angle, distance, BLUE);
		current_angle += FOV_RADIANS / WIDTH;
		x++;
	}
}

// static double	get_x_bitmap(t_img img, double wall_point)
// {
// 	return (fmodf(wall_point * (img.width / TILE_SIZE), img.width));
// }

double	find_wall_distance(t_maze *maze, double angle)
{
	t_vector	vertical_wall;
	t_vector	horizontal_wall;
	t_vector	vertical_first;
	t_vector	horizontal_first;
	t_dir 		direction;
	double		distance;


	direction = get_horizontal_direction(angle);
	horizontal_first = get_first_x_point(maze->player.pos, angle, direction);
	// horizontal_wall = get_wall_point_horizon(maze, maze->map, angle, direction, horizontal_first);
	horizontal_wall = get_wall_point_horizon(maze->map, angle, direction, horizontal_first);
	direction = get_vertical_direction(angle);
	vertical_first = get_first_y_point(maze->player.pos, angle, direction);
	// vertical_wall = get_wall_point_vert(maze, maze->map, angle, direction, vertical_first);
	vertical_wall = get_wall_point_vert(maze->map, angle, direction, vertical_first);
	distance = get_smallest_distance(maze->player.pos, horizontal_wall, vertical_wall, maze->img.orientation);
	return (distance);
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

double	compute_distance(t_vector a, t_vector b)
{
	double	norm;

	t_vector vector;
	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	norm = sqrt(vector.x * vector.x + vector.y * vector.y);

	return (norm);
}

double	get_smallest_distance(t_vector target, t_vector a, t_vector b, int *orientation)
{
	double distance_1;
	double distance_2;

	distance_1 = compute_distance(target, a);
	distance_2 = compute_distance(target, b);
	// if (distance_1 > distance_2)
	// 	*orientation = 1;
	// else
	// 	*orientation = 2;
	return (fmin(distance_1, distance_2));
}
