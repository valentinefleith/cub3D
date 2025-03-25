# include "cub3d.h"

static uint32_t	convert_hex_color(int *rgb)
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

static int	assign_color(t_map *map, char letter, int *rgb)
{
	static int	i = 0;

	if (letter == 'F' && map->floor_color == 0)
		map->floor_color = convert_hex_color(rgb);
	else if (letter == 'C' && map->ceilling_color == 0)
		map->ceilling_color = convert_hex_color(rgb);
	else if (letter == 'S' && !map->color_sequence[i])
	{
		map->color_sequence[i++] = convert_hex_color(rgb);
		return (SUCCESS);
	}
	else
	{
		free(rgb);
		return (map_error(DOUBLE_SYMB));
	}
	free(rgb);
	return (SUCCESS);
}

static int	get_color_sequence(t_map *map, char *line, int *rgb)
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
		return (KO);
	return (SUCCESS);
}

int	get_color(char *line, int *i)
{
	char	*color;
	int		result;
	int		start;

	color = NULL;
	start = *i;
	while (line[*i] && line[*i] != ',' && line[*i] != '\n' && line[*i] != '/')
		*i += 1;
	if (line[*i] && (line[*i] == ',' || line[*i] == '\n' || line[*i] == '/'))
	{
		color = ft_substr(line, start, (*i));
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

char	check_color_symbol(char *line)
{
	int		i;
	char	letter;

	if (!line)
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
