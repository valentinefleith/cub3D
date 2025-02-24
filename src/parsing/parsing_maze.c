#include "cub3d.h"

int	store_the_maze(int fd, char **maze)
{
	char	*line;
	int		i;

	if (!maze)
		return (map_error(ERROR_MAP), KO);
	i = 0;
	line = skip_beginning(fd);
	while (1)
	{
		if (!line)
			return (close(fd), SUCCESS);
		if (line && !check_maze_valid_symbol(line))
			return (map_error(EMPTY_LINE), free(line), close(fd), KO);
		maze[i] = ft_substr(line, 0, ft_strlen(line) - 1);
		if (!maze[i])
			return (map_error(ERROR_MAP), free(line), close(fd), KO);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), SUCCESS);
}

int	check_maze_valid_symbol(char *line)
{
	int	i;

	if (!line || line[0] == '\n') // if line is empty = invalid
		return (0);
	if (is_line_empty(line)) // if line is filled with only spaces = empty and invalid
		return (0);
	i = 0;
	while (line[i]) // maze is valid only if it contains the symbols below
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 32
			&& line[i] != 'N' && line[i] != 'S' 
			&& line[i] != 'W' && line[i] != 'E' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/*
 This function browses the file to height how many lines are needed for the map.
 TODO = add the calculation for the width + store that in struct dimension
*/
t_dimensions	get_maze_size(int fd, char *prev_line)
{
	t_dimensions dimensions;
	int 		height;
	int 		width;
	char		*line;
	
	dimensions.height = -1;
	dimensions.width = -1;
	if (!prev_line)
		return (map_error(ERROR_MAP), dimensions);
	height = 1;
	width = ft_strlen(prev_line);
	line = NULL;
	while (1)
	{
		if (line && check_maze_valid_symbol(line))
			height++;
		free(line);
		line = get_next_line(fd);
		if (!line) // when the file is ended quit the infinite loop
		{
			dimensions.height = height;
			// dimensions.width = width - 1; // TODO delete later when no more \n in the line!!!
			dimensions.width = width;
			return (close(fd), dimensions);
		}
		int current_width = ft_strlen(line);
		if (current_width > width)
			width = current_width;
	}
	dimensions.height = height;
	dimensions.width = width;
	return (close(fd), dimensions);
}

/*  Skip the beginning of the file to reach maze content */
char	*skip_beginning(int fd)
{
	char *line;

	line = NULL;
	while (!check_maze_valid_symbol(line))
	{
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	return (line);
}