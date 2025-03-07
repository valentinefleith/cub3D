# include "cub3d.h"

int	parsing_colors(char *line, t_map *map)
{
	int		i;
	int		j;
	int		letter;
	int		color;

	letter = check_color_symbol(line); // to know if it's for the floor or ceilling color
	if (!letter && !is_line_empty(line))
		return (map_error(INVALID), 0); // if nothing has been found = invalid
	j = 0;
	i = 2;
	if (is_line_empty(line))
		return (1);
	while (line[i] && line[i] != '\n')
	{
		color = find_color(&line[i]); // finds and converts color in an int
		if (color < 0 || color > 255)
			return (map_error(RANGE_RGB), 0);
		if (letter == 1)
			map->floor[j] = color;
		else
			map->celling[j] = color;
		j++;
		while (line && line[i] != ',' && line[i] != '\n') // skip what we've already parsed in find_color()
			i++;
		i++;
	}
	return (1);
}

int	find_color(char *line)
{
	int		i;
	char	*color;

	if (!line)
		return (-1);
	i = 0;
	color = NULL;
	while (line[i] && line[i] != ',' && line[i] != '\n')
		i++;
	if (line && (line[i] == ',' || line[i] == '\n'))
		color = ft_substr(line, 0, i);
	if (!color)
		return (-1);
	i = ft_atoi(color);
	free(color);
	return (i);
}

int	check_color_symbol(char *line)
{
	int	i;
	int	letter;

	if (!line)
		return (0);
	letter = 0;
	if (!ft_strncmp(line, "F ", 2))
		letter = 1;
	else if (!ft_strncmp(line, "C ", 2))
		letter = 2;
	else
		return (0);
	i = 2;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && line[i] != ',' && line[i] == '\n')
			return (0);
		i++;
	}
	return (letter);
}