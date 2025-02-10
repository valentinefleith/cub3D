#include "cub3d.h"

int	store_the_maze(int fd, char **maze)
{
	char	*line;
	int		i;

	if (!maze)
		return (map_error(ERROR_MAP), KO);
	line = NULL;
	i = 0;
	skip_beginning(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), SUCCESS);
		if (line && !check_maze_valid_symbol(line))
			return (map_error(EMPTY_LINE), free(line), close(fd), KO);
		maze[i] = ft_strdup(line);
		if (!maze[i])
			return (map_error(ERROR_MAP), free(line), close(fd), KO);
		i++;
		free(line);
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
 This function browses the file to count how many lines are needed for the map.
*/
int	get_maze_size(int fd, char *prev_line)
{
	int 	count;
	char	*line;
	
	if (!prev_line)
		return (map_error(ERROR_MAP), -1);
	count = 0;
	line = NULL;
	while (1)
	{
		if (line && check_maze_valid_symbol(line))
			count++;
		free(line);
		line = get_next_line(fd);
		if (!line) // when the file is ended quit the infinite loop
			return (close(fd), count);
	}
	return (close(fd), count);
}

/*  Skip the beginning of the file to reach maze content */
void	skip_beginning(int fd)
{
	char *line;

	line = NULL;
	while (!check_maze_valid_symbol(line))
	{
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}