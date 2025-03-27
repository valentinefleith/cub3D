/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:58:26 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 16:59:00 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
