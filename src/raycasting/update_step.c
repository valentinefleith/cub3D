#include "cub3d.h"

void	increment_step(t_raycast *rc, t_vector player, t_vector map)
{
	if (rc->ray.x < 0)
		update_negative_step(rc, player.x, map.x, 'x');
	else
		update_positive_step(rc, player.x, map.x, 'x');
	if (rc->ray.y < 0)
		update_negative_step(rc, player.y, map.y, 'y');
	else
		update_positive_step(rc, player.y, map.y, 'y');
}

void	update_negative_step(t_raycast *rc, int player, int cell_px, char coordinates)
{
	if (coordinates == 'x')
	{
		rc->step_orientation.x = -1;
		rc->step_size.x = (player - cell_px) * rc->delta_dist.x;
	}
	else
	{
		rc->step_orientation.y = -1;
		rc->step_size.y = (player - cell_px) * rc->delta_dist.y;
	}
}

void	update_positive_step(t_raycast *rc, int player, int cell_px, char coordinates)
{
	if (coordinates == 'x')
	{
		rc->step_orientation.x = 1;
		rc->step_size.x = (player + 1.0 - cell_px) * rc->delta_dist.x;
	}
	else
	{
		rc->step_orientation.y = 1;
		rc->step_size.y = (player + 1.0 - cell_px) * rc->delta_dist.y;
	}
}
