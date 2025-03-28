/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:25:40 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 14:30:44 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing_colors(char *line, t_map *map)
{
	int		i;
	int		index;
	int		letter;
	int		*rgb;

	letter = check_color_symbol(line);
	if (letter != 'F' && letter != 'C' && letter != 'S')
		return (KO);
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (map_error(ERROR_MAP));
	if (letter == 'S')
		return (get_color_sequence(map, line, rgb));
	i = 2;
	index = 0;
	while (index < 3)
	{
		rgb[index] = get_color(line, &i);
		if (rgb[index] == -1)
			return (free(rgb), KO);
		index++;
	}
	if (!assign_color(map, letter, rgb))
		return (free(rgb), KO);
	return (SUCCESS);
}

int	get_color(char *line, int *i)
{
	char	*color;
	int		result;
	int		start;

	if (!ft_isdigit(line[*i]) && *i == 2)
		return (-1);
	color = NULL;
	start = *i;
	while (line[*i] && line[*i] != ',' && line[*i] != '\n' && line[*i] != '/')
		*i += 1;
	if (line[*i] && (line[*i] == ',' || line[*i] == '\n' || line[*i] == '/'))
	{
		color = ft_substr(line, start, (*i) - start);
		*i += 1;
		if (line[*i] && (line[*i] == ',' || line[*i] == '/'))
			return (free(color), map_error(INVALID), -1);
	}
	if (!color)
		return (-1);
	result = ft_atoi(color);
	free(color);
	if (result < 0 || result > 255)
		return (map_error(RANGE_RGB), -1);
	return (result);
}

static int	color_end_checking(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n' && !ft_isdigit(line[len - 2]))
		return (map_error(INVALID));
	return (SUCCESS);
}
char	check_color_symbol(char *line)
{
	int		i;
	char	letter;

	if (!line || !color_end_checking(line))
		return (0);
	letter = 0;
	if (line[0] == 'F' || line[0] == 'C' || line[0] == 'S')
		letter = line[0];
	else
		return (0);
	if (line[1] != ' ')
		return (KO);
	i = 2;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != '\n')
		{
			if (!(letter == 'S' && line[i] == '/'))
				return (KO);
		}
		i++;
	}
	return (letter);
}

int	assign_color(t_map *map, char letter, int *rgb)
{
	static int	i = 0;

	if (letter == 'F' && (int)map->floor_color == -1)
		map->floor_color = convert_hex_color(rgb);
	else if (letter == 'C' && (int)map->ceilling_color == -1)
		map->ceilling_color = convert_hex_color(rgb);
	else if (letter == 'S' && !map->color_sequence[i])
	{
		map->color_sequence[i++] = convert_hex_color(rgb);
		return (SUCCESS);
	}
	else
		return (map_error(DOUBLE_SYMB));
	free(rgb);
	return (SUCCESS);
}
