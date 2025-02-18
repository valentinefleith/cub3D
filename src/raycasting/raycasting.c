#include "cub3d.h"

void	update_raycast(t_raycast *rc, int x, int width)
{
	rc->camera.x = 2 * x / (double)width - 1;
	rc->ray.x = rc->view_dir.x + rc->plane.x * rc->camera.x;
	rc->ray.y = rc->view_dir.y + rc->plane.y * rc->camera.y;
	// Protection d'une division par zero
	if (rc->ray.x == 0)
		rc->delta_dist.x = 1e30;
	else
		rc->delta_dist.x = abs(1 / (int)rc->ray.x);
	if (rc->ray.y == 0)
		rc->delta_dist.y = 1e30;
	else
		rc->delta_dist.y = abs(1 / (int)rc->ray.y);
}

void	raycasting(t_maze *game, int map_w, t_vector player)
{
	t_raycast	rc;
	t_vector	map;
	int			x;

	x = 0;
	while (x < map_w)
	{
		update_raycast(&rc, x, map_w);
		map.x = (int)player.x;
		map.y = (int)player.y;
		increment_step(&rc, player, map);
		if (find_wall(&rc, game->map->maze, &map) == 0)
			draw(game, &rc, x, 0);
		else
			draw(game, &rc, x, 1);
		x++;
	}
}

int	find_wall(t_raycast *rc, char **maze, t_vector *map)
{
	bool		wall_hit;
	int			wall_orientation;

	wall_hit = false;
	while (!wall_hit)
	{
		if (rc->step_size.x < rc->step_size.y)
		{
			rc->step_size.x += rc->delta_dist.x;
			map->x += rc->step_orientation.x;
			wall_orientation = 0;
		}
		else
		{
			rc->step_size.y += rc->delta_dist.y;
			map->y += rc->step_orientation.y;
			wall_orientation = 1;
		}
		if (maze[(int)map->x][(int)map->y] == '1')
			wall_hit = true;
	}
	return (wall_orientation);
}

t_raycast init_raycasting(void)
{
	t_raycast rc;

	rc.plane.x = 0.0;
	rc.plane.y = 0.66;
	rc.view_dir.x = -1.0;
	rc.view_dir.y = 0.0;
	rc.camera.x = 0;
	rc.camera.y = 0;
	rc.player.x = 3.0;
	rc.player.y = 3.0;
	rc.ray.x = 0;
	rc.ray.y = 0;
	rc.step_size.x = 0;
	rc.step_size.y = 0;
	rc.step_orientation.x = 0;
	rc.step_orientation.y = 0;
	rc.delta_dist.x = 0;
	rc.delta_dist.y = 0;
	return (rc);
}
