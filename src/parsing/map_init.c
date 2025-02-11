#include "map.h"

/* Parsing the map's file and Initialization of the structure */
int	init_map(int args, char *filename, t_map *map)
{
	int	fd;

	if (args != 2)
		return (map_error(MISSING_MAP));
	if (check_filename_validity(filename))
		return (KO);
	map->textures_path = init_tab(4); 
	if (parsing_env_map_data(filename, map) != SUCCESS)
		return (free_path(map->textures_path), KO);
	if (map->heigth == -1)
		return (map_error(FILE_MAP));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (map_error(FILE_MAP), free_path(map->textures_path), KO);
	map->maze = init_tab(map->heigth);
	if (store_the_maze(fd, map->maze) != SUCCESS)
		return (free_map(map), KO);
	// map->width = WIDTH;
	return (SUCCESS);
}

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

char	**init_tab(int len)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = NULL;
		i++;
	}
	tab[i] = NULL;
	return (tab);
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
	{
		if (line[i] == '\n') // if line is filled with only spaces = empty
			return (1);
		i++;
	}
	return (0);
}