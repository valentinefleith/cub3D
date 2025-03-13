#include "cub3d.h"

int	store_maze(char **maze, int width, char *line, int index)
{
	if (!line || !maze)
		return (KO);
	remove_spaces(line);
	if ((int)(ft_strlen(line) - 1) < width)
		maze[index] = resize_line_with_walls(line, width);
	else
		maze[index] = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!maze[index])
		return (map_error(ERROR_MAP), KO);
	return (SUCCESS);
}

static int	parsing_line(char *line, int index, int height)
{
	if (!line || is_line_empty(line))
		return (map_error(EMPTY_LINE));
	if (!check_maze_valid_symbol(line, true))
		return (KO);
	if (!check_maze_edges(line, index, height))
		return (map_error(EDGES));
	return (SUCCESS);
}

int	maze_parsing(int fd, char **maze, int height, int width)
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
			break ;
		if (!parsing_line(line, i, height))
		{
			free(line);
			close(fd);
			return (KO);
		}
		if (store_maze(maze, width, line, i))
			i++;
		else
			return (KO);
		free(line);
		line = read_file(fd);
	}
	return (SUCCESS);
}
