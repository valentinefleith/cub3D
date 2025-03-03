#include "cub3d.h"

void	draw_rectangle(t_maze *maze, t_point center_pos, int width,
		int height, int color)
{
	int	start_i;
	int	start_j;

	start_i = center_pos.x - (width / 2);
	start_j = center_pos.y - (height / 2);
	for (int i = start_i; i < start_i + width; i++)
	{
		for (int j = start_j; j < start_j + height; j++)
		{
			my_mlx_pixel_put(&(maze->img), i, j, color);
		}
	}
}

void	draw_line(t_maze *maze, t_point start, t_point end, int color)
{
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	error;
	int	error2;

	delta_x = abs(end.x - start.x);
	delta_y = abs(end.y - start.y);
	if (start.x < end.x)
		step_x = 1;
	else
		step_x = -1;
	if (start.y < end.y)
		step_y = 1;
	else
		step_y = -1;
	error = delta_x - delta_y;
	while (start.x != end.x || start.y != end.y)
	{
		my_mlx_pixel_put(&(maze->img), start.x, start.y, color);
		error2 = 2 * error;
		if (error2 > -delta_y)
		{
			error -= delta_y;
			start.x += step_x;
		}
		if (error2 < delta_x)
		{
			error += delta_x;
			start.y += step_y;
		}
	}
}

void	draw_line_from_angle(t_maze *maze, t_point point, double angle,
		int size, int color)
{
	t_point	endpoint;

	endpoint.y = point.y + (int)(size * sin(angle));
	endpoint.x = point.x + (int)(size * cos(angle));
	// printf("ENDPOINT.X = %d // ENDPOINT.Y = %d // ANGLE = %f\n", endpoint.y, endpoint.x, angle);
	if (point.y < 0 || point.x > WIDTH || point.x < 0 || point.y > HEIGHT || endpoint.y < 0 || endpoint.y > HEIGHT)
		return ;
	draw_line(maze, point, endpoint, color);
}

void draw_grid(t_maze *maze)
{
	t_point start;
	start.x = 0;
	start.y = 0;

	t_point end;
	end.x = 0;
	end.y = HEIGHT;

	while (start.x <= WIDTH) {
		draw_line(maze, start, end, BLACK);
		start.x += TILE_SIZE;
		end.x += TILE_SIZE;
	}

	start.x = 0;
	start.y = 0;

	end.x = WIDTH;
	end.y = 0;

	while (start.y <= HEIGHT) {
		draw_line(maze, start, end, BLACK);
		start.y += TILE_SIZE;
		end.y += TILE_SIZE;
	}

}