#include "cub3d.h"

/* Initialization and parsing of the map's structure */
int	init_map(int args, char *filename, t_map *map)
{
	int	len;

	if (args != 2)
		return (map_error(MISSING_MAP));
	len = 0;
	map->p_x = 0;
	map->p_y = 0;
	map->map_w = WIDTH;
	map->map_h = HEIGHT;
	if (check_filename_validity(filename))
		return (KO);
	len = get_map_size(filename); // to know how many cells to allocate
	if (len == -1)
		return (map_error(FILE_MAP));
	map->map = malloc(sizeof(char *) * (len + 1));
	if (!map->map)
		return (map_error(ERROR_MAP));
	map->map = store_the_map(filename, map->map);
	// then fill the map for :
	// -> check if map unclosed + store width and heigth
	// -> check if only one player position and store it's coordinates and start's direction
	return (SUCCESS);
}

int	check_filename_validity(char *filename)
{
	if (!filename)
		return (map_error(ERROR_MAP), KO);
	if (!ft_strnstr(filename, ".cub", ft_strlen(filename)) 
		|| filename[ft_strlen(filename) - 1] != 'b')
		return (map_error(NAME_MAP), KO);
	return (SUCCESS);
}

/*
 This function browses the file to count how many lines are needed for the map.
*/
int	get_map_size(char *filename)
{
	int 	fd;
	int 	count;
	char	*line;
	
	if (!filename)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		while (line && check_map_valid_symbol(line)) // count lines only if they're valid
		{
			count++;
			line = get_next_line(fd);
		}
		if (!line) // when the file is ended quit the infinite loop
			return (free(line), close(fd), count);
	}
	return (close(fd), count);
}

char	**store_the_map(char *filename, char **map)
{
	char	*line;
	int		i;
	int		fd;

	line = NULL;
	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (map_error(FILE_MAP), free_map(map));
	while (1)
	{
		line = get_next_line(fd);
		while (line && check_map_valid_symbol(line)) // copy only lines that are valid
		{
			map[i] = ft_strdup(line);
			if (!map[i])
				return (map_error(ERROR_MAP), close(fd), free_map(map));
			i++;
			map[i] = NULL;
			line = get_next_line(fd);
		}
		if (!line)
			return (free(line), close(fd), map);
	}
	return (close(fd), map);
}

int	check_map_valid_symbol(char *line)
{
	int	i;

	if (!line || line[0] == '\n') // if line is empty = invalid
		return (0);
	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	if (line[i] == '\n') // if line is filled with only spaces = invalid
		return (0);
	i = 0;
	while (line[i]) // map is valid only if it contains the symbols below
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 32
			&& line[i] != 'N' && line[i] != 'S' 
			&& line[i] != 'W' && line[i] != 'E' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	map_error(int error_code)
{
	ft_putstr_fd("\e[1;31mError: ", 2);
	if (error_code == MISSING_MAP)
		ft_putendl_fd("map is missing as argument\e[0m", 2);
	else if (error_code == MISSING_MAP)
		ft_putendl_fd("while parsing the map\e[0m", 2);
	else if (error_code == NAME_MAP)
		ft_putendl_fd("map's extension name must be *.cub\e[0m", 2);
	else if (error_code == FILE_MAP)
		ft_putendl_fd("cannot open this file\e[0m", 2);
	else if (error_code == EMPTY_MAP)
		ft_putendl_fd("map file is empty\e[0m", 2);
	return (KO);
}

char	**free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
	if (map)
	{
		free(map);
		map = NULL;
	}
	return (map);
}
