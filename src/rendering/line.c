/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:24:19 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 18:26:00 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	compute_step(t_point start, t_point end)
{
	t_point	step;

	if (start.x < end.x)
		step.x = 1;
	else
		step.x = -1;
	if (start.y < end.y)
		step.y = 1;
	else
		step.y = -1;
	return (step);
}

void	draw_line(t_maze *maze, t_point start, t_point end, int color)
{
	t_point	delta;
	t_point	step;
	int		error;
	int		error2;

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	step = compute_step(start, end);
	error = delta.x - delta.y;
	while (start.x != end.x || start.y != end.y)
	{
		my_mlx_pixel_put(&(maze->img), start.x, start.y, color);
		error2 = 2 * error;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			start.x += step.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			start.y += step.y;
		}
	}
}

t_line_characteristics	to_line_characteristics(double angle, double size,
	int color)
{
	t_line_characteristics	characteristic;

	characteristic.angle = angle;
	characteristic.size = size;
	characteristic.color = color;
	return (characteristic);
}

void	draw_line_from_angle(t_maze *maze, t_point start_point,
		t_line_characteristics characteristics)
{
	t_point	endpoint;

	endpoint.y = start_point.y + (characteristics.size
			* sin(characteristics.angle));
	endpoint.x = start_point.x + (characteristics.size
			* cos(characteristics.angle));
	if (endpoint.x < 0)
		endpoint.x = 1;
	if (endpoint.y < 0)
		endpoint.y = 1;
	draw_line(maze, start_point, endpoint, characteristics.color);
}
