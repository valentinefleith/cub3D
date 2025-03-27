/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:59:38 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 17:01:29 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_wall_distance(t_vector player_point, t_vector wall_point, \
		double player_angle, double current_angle)
{
	double	distance;

	distance = compute_distance(player_point, wall_point);
	distance = distance * cos(current_angle - player_angle);
	return (distance);
}

double	compute_distance(t_vector a, t_vector b)
{
	t_vector	vector;
	double		norm;

	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	norm = sqrt(vector.x * vector.x + vector.y * vector.y);
	return (norm);
}

t_vector	get_closest_point(t_vector target, t_vector a, t_vector b, \
			bool *horizontal)
{
	double	distance_1;
	double	distance_2;

	distance_1 = compute_distance(target, a);
	distance_2 = compute_distance(target, b);
	if (fmin(distance_1, distance_2) == distance_1)
	{
		*horizontal = true;
		return (a);
	}
	*horizontal = false;
	return (b);
}
