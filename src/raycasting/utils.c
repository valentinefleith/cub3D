#include "cub3d.h"
#include "raycasting.h"

double	normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return (angle);
}

void	draw_fov(t_maze *maze)
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