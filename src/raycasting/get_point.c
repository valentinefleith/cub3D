#include "cub3d.h"
#include "raycasting.h"

t_position get_first_y_point(t_position player, double angle, t_dir direction)
{
	t_position	first_point;

	if (direction == left)
		first_point.x = floor(player.x / TILE_SIZE) * TILE_SIZE - 1;
	else
		first_point.x = floor(player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	first_point.y = player.y - (player.x - first_point.x) * tan(angle);
	return (first_point);
}

t_position get_first_x_point(t_position player_pos, double angle, t_dir direction)
{
	t_position	first_point;

	if (direction == up)
		first_point.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE - 1;
	else
		first_point.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	first_point.x = player_pos.x - (player_pos.y - first_point.y) / tan(angle);
	return (first_point);
}

// t_position get_wall_point_horizon(t_map *map, double angle, t_dir direction, t_position point)
t_position get_wall_point_horizon(t_maze *maze, t_map *map, double angle, t_dir direction, t_position point)// proto to debug
{
	int	x_step;
	int	y_step;
	
	x_step = floor(TILE_SIZE / tan(angle));
	if (direction == down)
		x_step = -x_step;
	y_step = TILE_SIZE;
	if (direction == up)
		y_step = -TILE_SIZE;
	while (!is_wall_point(map, point))
	{
		draw_rectangle(maze, point, 5, 5, RED);
		point.x -= x_step;
		point.y += y_step;
	}
	return point;

}

t_position	get_wall_point_vert(t_maze *maze, t_map *map, double angle, t_dir direction, t_position point)
{
	int	x_step;
	int	y_step;
	
	x_step = TILE_SIZE;
	if (direction == left)
		x_step *= -1;
	y_step = TILE_SIZE * tan(angle);
	if ((get_horizontal_direction(angle) == up && y_step > 0) 
		|| (get_horizontal_direction(angle) == down && y_step < 0))
		y_step *= -1;
	while (!is_wall_point(map, point))
	{
		if (point.y < HEIGHT && point.y >= 0)
			draw_rectangle(maze, point, 5, 5, BLACK);
		point.x += x_step;
		point.y += y_step;
	}
	return point;
}
