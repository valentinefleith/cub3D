#include "cub3d.h"
#include "player.h"

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return (angle);
}

static t_position get_first_intersect_y(t_position player_pos, double angle, bool is_facing_up)
{
	t_position	first_intersect;

	(void)is_facing_up;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2) // is_left
		first_intersect.x = floor(player_pos.x / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE - 1;
	else
		first_intersect.x = floor(player_pos.x / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE + MAP_SQUARE_SIZE;
	// if (angle > M_PI && angle < 2 * M_PI)
	// 	first_intersect.y = player_pos.y - (player_pos.x - first_intersect.x) * tan(angle);
	// else
		first_intersect.y = player_pos.y - (player_pos.x - first_intersect.x) * tan(angle);
	return (first_intersect);
}

static t_position get_first_intersect_x(t_position player_pos, double angle, bool is_facing_up)
{
	t_position	first_intersect;

	if (is_facing_up)
		first_intersect.y = floor(player_pos.y / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE - 1;
	else
		first_intersect.y = floor(player_pos.y / MAP_SQUARE_SIZE) * MAP_SQUARE_SIZE + MAP_SQUARE_SIZE;
	first_intersect.x = player_pos.x - (player_pos.y - first_intersect.y) / tan(angle);
	return (first_intersect);
}

static bool is_facing_up(double angle)
{
	return (angle > M_PI && angle < 2 * M_PI);
}

static bool is_facing_left(double angle)
{
	double pi = M_PI / 2;
	double pipi = 3 * M_PI / 2;
	printf("angle = %f\n", angle);
	printf("PI / 2 = %f\n", pi);
	printf("3 * PI / 2 = %f\n", pipi);
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		return (true);
	return (false);
}

static int	find_x_step(double angle)
{
	if (angle < M_PI)
		return (-floor(MAP_SQUARE_SIZE / tan(angle))); // maybe floor
	return (floor(MAP_SQUARE_SIZE / tan(angle)));
}

static int	find_y_step(bool facing_up)
{
	if (facing_up)
		return (-MAP_SQUARE_SIZE);
	return (MAP_SQUARE_SIZE);
}

static bool is_wall_point(t_map *map, t_position point)
{
	t_position	grid;

	if (!map)
		return (false);
	grid.x = floor(point.x / MAP_SQUARE_SIZE);
	grid.y = floor(point.y / MAP_SQUARE_SIZE);
	// printf("\ngrid.x = %d // grid.y = %d \n", grid.x, grid.y);
	if (grid.y < 0 || grid.x >= map->dimensions.width || grid.y > map->dimensions.height || grid.x < 0)
		return (true);
	if (map->maze[grid.y] && map->maze[grid.y][grid.x])
		return (map->maze[grid.y][grid.x] == '1');
	return (false);
}
static t_position get_wall_point_horizon(t_maze *maze, t_map *map, double angle, bool facing_up, t_position point)
{
	int			x_step;
	int			y_step;
	
	x_step = find_x_step(angle);
	y_step = find_y_step(facing_up);
	while (!is_wall_point(map, point))
	{
		draw_rectangle(maze, point, 5, 5, RED);
		point.x -= x_step;
		point.y += y_step;
	}
	return point;

}

static t_position get_wall_point_vert(t_maze *maze, t_map *map, double angle, bool facing_up, t_position point)
{
	int			x_step;
	int			y_step;
	
	x_step = MAP_SQUARE_SIZE;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		x_step *= -1;
	y_step = MAP_SQUARE_SIZE * tan(angle);
	if ((facing_up && y_step > 0) || (!facing_up && y_step < 0))
		y_step *= -1;
	while (!is_wall_point(map, point))
	{
		if (point.y < HEIGHT && point.y >= 0)
			draw_rectangle(maze, point, 5, 5, BLACK);
		point.x += x_step;
		point.y += y_step;
	}
	return point;
	/*
		while next intersection != wall
			-> get next intersection with x_step and y_step
		return next intersection
	*/
}


static int	compute_distance(t_position a, t_position b)
{
	int	norm;

	t_position vector;
	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	norm = sqrt(vector.x * vector.x + vector.y * vector.y);

	return (norm);
}

static	int	get_smallest_distance(t_position target, t_position a, t_position b)
{
	int distance_1;
	int distance_2;

	distance_1 = compute_distance(target, a);
	distance_2 = compute_distance(target, b);
	return (fmin(distance_1, distance_2));
}

static int	find_wall_distance(t_maze *maze, double angle)
{
	t_position	vertical_wall;
	t_position	horizontal_wall;
	t_position	vertical_first;
	t_position	horizontal_first;
	bool 		facing_up;
	int			distance;


	facing_up = is_facing_up(angle);
	horizontal_first = get_first_intersect_x(maze->player.pos, angle, facing_up);
	horizontal_wall = get_wall_point_horizon(maze, maze->map, angle, facing_up, horizontal_first);

	vertical_first = get_first_intersect_y(maze->player.pos, angle, facing_up);
	vertical_wall = get_wall_point_vert(maze, maze->map, angle, facing_up, vertical_first);
	// if (vertical_first.x < WIDTH && vertical_first.x > 0 && vertical_first.y < HEIGHT && vertical_first.y > 0)
	// 	draw_rectangle(maze, vertical_first, 5, 5, BLACK);

	// draw_rectangle(maze, horizontal_wall, 5, 5, BLUE);
	// draw_rectangle(maze, vertical_wall, 5, 5, BLUE);
	distance = get_smallest_distance(maze->player.pos, horizontal_wall, vertical_wall);
	return (distance);

}

static void draw_fov(t_maze *maze)
{
	double	player_direction = maze->player.looking_angle;
	double first_ray = player_direction - FOV_RADIANS / 2;
	double last_ray = player_direction + FOV_RADIANS / 2;
	double current_angle = first_ray;
	while (current_angle < last_ray)
	{
		int size_til_next_wall = find_wall_distance(maze, normalize_angle(current_angle));
		draw_line_from_angle(maze, maze->player.pos, current_angle, size_til_next_wall, BLUE);
	 	current_angle += 0.1;
	}
}

void	raycasting(t_maze *maze)
{
	t_position	center_pos;

	center_pos.y = MAP_SQUARE_SIZE / 2;
	for (int i = 0; i < maze->map->dimensions.height; i++)
	{
		center_pos.x = MAP_SQUARE_SIZE / 2;
		for (int j = 0; j < maze->map->dimensions.width; j++)
		{
			if (maze->map->maze[i][j] == '1')
				draw_rectangle(maze, center_pos, MAP_SQUARE_SIZE,
					MAP_SQUARE_SIZE, WHITE);
			else
				draw_rectangle(maze, center_pos, MAP_SQUARE_SIZE,
					MAP_SQUARE_SIZE, GREY);
			center_pos.x = center_pos.x + MAP_SQUARE_SIZE;
		}
		center_pos.y = center_pos.y + MAP_SQUARE_SIZE;
	}
	draw_grid(maze);
	draw_rectangle(maze, maze->player.pos, PLAYER_WIDTH_PX, PLAYER_WIDTH_PX,
		GREEN);
	draw_line_from_angle(maze, maze->player.pos, maze->player.looking_angle,
		70, RED);
	draw_fov(maze);
}