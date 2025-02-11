#include "map.h"

int	map_error(int error_code)
{
	ft_putendl_fd("\e[1;31mError", 2);
	if (error_code == MISSING_MAP)
		ft_putendl_fd("> Map is missing as argument\e[0m", 2);
	else if (error_code == ERROR_MAP)
		ft_putendl_fd("> While parsing the map\e[0m", 2);
	else if (error_code == NAME_MAP)
		ft_putendl_fd("> Map's extension name must be *.cub\e[0m", 2);
	else if (error_code == FILE_MAP)
		ft_putendl_fd("> Cannot open this file\e[0m", 2);
	else if (error_code == EMPTY_LINE)
		ft_putendl_fd("> An empty line has been found in the map\e[0m", 2);
	else if (error_code == INVALID)
		ft_putendl_fd("> An invalid format or symbol has been detected\e[0m", 2);
	else if (error_code == RANGE_RGB)
		ft_putendl_fd("> RGB color's range must be between 0 and 255\e[0m", 2);
	return (KO);
}

int	free_map(t_map *map)
{
	if (!map)
		return (KO);
	map->textures_path = free_path(map->textures_path);
	map->maze = free_double_tab(map->maze);
	return (SUCCESS);
}

char	**free_double_tab(char **map)
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

char	**free_path(char **tab)
{
	if (!tab)
		return (NULL);
	if (tab[0])
		free(tab[0]);
	if (tab[1])
		free(tab[1]);
	if (tab[2])
		free(tab[2]);
	if (tab[3])
		free(tab[3]);
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
	return (tab);
}
