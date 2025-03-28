/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:43:50 by vafleith          #+#    #+#             */
/*   Updated: 2025/03/27 18:17:39 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rectangle_characteristics	to_rectangle_characteristics(int height,
	int width, int color)
{
	t_rectangle_characteristics	rectangle_characteristics;

	rectangle_characteristics.height = height;
	rectangle_characteristics.width = width;
	rectangle_characteristics.color = color;
	return (rectangle_characteristics);
}

void	draw_rectangle(t_maze *maze, t_point center_pos,
	t_rectangle_characteristics characteristics)
{
	int	start_i;
	int	start_j;
	int	i;
	int	j;

	start_i = center_pos.x - (characteristics.width / 2);
	start_j = center_pos.y - (characteristics.height / 2);
	i = start_i;
	while (i < start_i + characteristics.width)
	{
		j = start_j;
		while (j < start_j + characteristics.height)
		{
			my_mlx_pixel_put(&(maze->img), i, j, characteristics.color);
			j++;
		}
		i++;
	}
}
