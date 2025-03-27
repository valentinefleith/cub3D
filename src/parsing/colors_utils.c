/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:27:25 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:07 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	convert_hex_color(int *rgb)
{
	int			red;
	int			green;
	int			blue;
	uint32_t	result;

	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	result = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
	return (result);
}

int	get_color_sequence(t_map *map, char *line, int *rgb)
{
	int	sequence_index;
	int	rgb_index;
	int	i;

	sequence_index = 0;
	i = 2;
	while (sequence_index < 3)
	{
		rgb_index = 0;
		while (rgb_index < 3)
		{
			rgb[rgb_index] = get_color(line, &i);
			if (rgb[rgb_index] == -1)
				return (free(rgb), KO);
			rgb_index++;
		}
		if (!assign_color(map, 'S', rgb))
			return (KO);
		sequence_index++;
	}
	free(rgb);
	return (SUCCESS);
}
