#include "cub3d.h"
#include "raycasting.h"

t_dir	get_vertical_direction(double angle)
{
	t_dir	direction;

	if (angle < (M_PI / 2) || angle > (3 * M_PI / 2))
		direction = facing_right;
	else
		direction = facing_left;
	return (direction);	
}

t_dir	get_horizontal_direction(double angle)
{
	t_dir	direction;

	if (angle > 0 && angle < M_PI)
		direction = facing_down;
	else
		direction = facing_up;
	return (direction);
}
