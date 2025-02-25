/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:43:50 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/12 10:32:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_texture(t_maze *maze, t_vector wall_point, double wall_height, int y, int x)
{
	int	offset;
	// Get the pixel coordinates in the texture
	if (maze->img.orientation == 1)
		maze->img.x = fmodf(wall_point.x * maze->img.width / TILE_SIZE, maze->img.width);
	else
		maze->img.x = fmodf(wall_point.y * maze->img.width / TILE_SIZE, maze->img.width);
		// Calculate the scale from screen to texture
	offset = maze->img.height / wall_height;
	maze->img.y = ((offset * TILE_SIZE) / wall_height) / maze->img.line_length;
	int px_y = maze->img.y;
	int px_x = maze->img.x;
	int color = *(int *)(maze->img.textures[0] + (px_y * maze->img.line_length + px_x * (maze->img.bits_per_pixel / 8)));
	my_mlx_pixel_put(&(maze->img), x, y, color);
	// Set main image data to the texture image data based on px_x and px_y
	// maze->img.addr[px_y + px_x * maze->img.bits_per_pixel / 8] = maze->img.textures[0][px_x + px_y * maze->img.bits_per_pixel / 8];
	// maze->img.addr[px_y + px_x * maze->img.bits_per_pixel / 8 + 1] = maze->img.textures[0][px_x + px_y * maze->img.bits_per_pixel / 8 + 1];
	// maze->img.addr[px_y + px_x * maze->img.bits_per_pixel / 8 + 2] = maze->img.textures[0][px_x + px_y * maze->img.bits_per_pixel / 8 + 2];
}

void	draw_wall(t_maze *maze, t_vector wall_point, double wall_height, int x)
{
	int	y;
	int	end_y;
	int	offset;

	end_y = (HEIGHT / 2) + (wall_height / 2);
	if (HEIGHT < end_y)
		end_y = HEIGHT;
	y = (HEIGHT / 2) - (wall_height / 2);
	if (y < 0)
		y = 0;
	// Get the pixel coordinates in the texture
	if (maze->img.orientation == 1)
		maze->img.x = fmodf(wall_point.x * maze->img.width / TILE_SIZE, maze->img.width);
	else
		maze->img.x = fmodf(wall_point.y * maze->img.width / TILE_SIZE, maze->img.width);
	// Calculate the scale from screen to texture
	// offset = maze->img.height / wall_height;
	offset = (y - HEIGHT / 2 + wall_height / 2) *  1.0 * TILE_SIZE / maze->img.line_length;
	maze->img.y = ((offset * TILE_SIZE) / wall_height) / maze->img.line_length;
	int px_y = maze->img.y;
	int px_x = maze->img.x;
	while (y < end_y)
	{
		offset += 1.0 * TILE_SIZE / maze->img.line_length;
		// int color = maze->img.textures[0][TILE_SIZE * ((int)offset & (TILE_SIZE - 1)) + px_x];
		// maze->img.addr[TILE_SIZE * ((int)offset & (TILE_SIZE - 1)) + px_x] = maze->img.textures[0][TILE_SIZE * ((int)offset & (TILE_SIZE - 1)) + px_x];
		// setup_texture(maze, wall_point, wall_height, y, x);
		// my_mlx_pixel_put(&(maze->img), x, y, RED);
		y++;
	}
}

void	draw_rectangle(t_maze *maze, t_position center_pos, int width,
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

void	draw_line(t_maze *maze, t_position start, t_position end, int color)
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

void	draw_line_from_angle(t_maze *maze, t_position point, double angle,
		int size, int color)
{
	t_position	endpoint;

	endpoint.y = point.y + (int)(size * sin(angle));
	endpoint.x = point.x + (int)(size * cos(angle));
	// printf("ENDPOINT.X = %d // ENDPOINT.Y = %d // ANGLE = %f\n", endpoint.y, endpoint.x, angle);
	if (point.y < 0 || point.x > WIDTH || point.x < 0 || point.y > HEIGHT || endpoint.y < 0 || endpoint.y > HEIGHT)
		return ;
	draw_line(maze, point, endpoint, color);
}

void draw_grid(t_maze *maze)
{
	t_position start;
	start.x = 0;
	start.y = 0;

	t_position end;
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