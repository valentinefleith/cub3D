/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:12:01 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 18:13:35 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += (2 * M_PI);
	if (angle == 0)
		angle = 0;
	while (angle > 2 * M_PI)
		angle -= (2 * M_PI);
	return (angle);
}
