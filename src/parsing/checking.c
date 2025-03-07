# include "cub3d.h"

/* Add more security with recoder la fonction python endswith()*/
int	check_filename_validity(char *filename)
{
	if (!filename)
		return (map_error(ERROR_MAP), KO);
	if (!ft_strnstr(filename, ".cub", ft_strlen(filename)) 
		|| filename[ft_strlen(filename) - 1] != 'b')
		return (map_error(NAME_MAP), KO);
	return (SUCCESS);
}

int	is_line_empty(char *line)
{
	int	i;

	if (!line)
		return (0);
	if (line[0] == '\n')
		return (1);
	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	if (line[i] == '\n' || line[i] == '\0') // if line is filled with only spaces = empty
		return (1);
	return (0);
}

int	check_maze_valid_symbol(char *line, bool msg_error)
{
	int	i;

	if (!line) // if line is empty = invalid
		return (0);
	if (is_line_empty(line)) // if line is filled with only spaces = empty and invalid
	{
		if (msg_error)
			map_error(EMPTY_LINE);
		return (0);
	}
	i = 0;
	while (line[i]) // maze is valid only if it contains the symbols below
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 32
			&& line[i] != 'N' && line[i] != 'S' 
			&& line[i] != 'W' && line[i] != 'E' && line[i] != '\n')
		{
			if (msg_error)
				map_error(INVALID);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_map_borders_edges(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != 32)
			return (KO);
		i++;
	}
	return (SUCCESS);
}

int	check_maze_edges(char *line, int index, int height)
{
	int	i;
	int	len;

	if (!line)
		return (KO);
	if ((index == 0 || index == height))
		return (check_map_borders_edges(line));
	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	len = ft_strlen(line) - 2;
	if (line[i] != '1' || line[len] != '1')
		return (KO);
	return (SUCCESS);
}
