#include "cub3d.h"

void	draw(t_maze *game, t_raycast *rc, int x, int wall_orientation)
{
	double	wall_dist;
	int		line_height;
	int		start;
	int		end;

	if (wall_orientation == 0)
		wall_dist = rc->step_size.x - rc->delta_dist.x;
	else
		wall_dist = rc->step_size.y - rc->delta_dist.y;
	line_height = (int)(HEIGHT / wall_dist);
	start = -line_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	// define wich wall to draw
	if (wall_orientation == 0)
		draw_wall(game, x, start, end, BLUE);
	else
		draw_wall(game, x, start, end, GREEN);
	// draw_ceilling(game, x, start);
	// draw_floor(game, x, end + 1);
}

void	draw_wall(t_maze *game, int x, int y_start, int y_end, int color)
{
	while (y_start <= y_end)
	{
		my_mlx_pixel_put(&game->img, x, y_start, color);
		y_start++;
	}
}

void	draw_ceilling(t_maze *game, int x, int y_end)
{
	int y_start;

	y_start = 0;
	while (y_start < y_end)
	{
		my_mlx_pixel_put(&game->img, x, y_start, WHITE);
		y_start++;
	}
}

void	draw_floor(t_maze *game, int x, int y_start)
{
	int y_end;

	y_end = HEIGHT;
	while (y_start < y_end)
	{
		my_mlx_pixel_put(&game->img, x, y_start, GREY);
		y_start++;
	}
}