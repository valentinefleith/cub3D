#include "cub3d.h"

static void	map_error_bis(int error_code)
{
	if (error_code == DOUBLE_SYMB)
		ft_putendl_fd("> Multiple lines concern the same symbol/data\e[0m", 2);
	else if (error_code == DIRECTORY)
		ft_putendl_fd("> The map file is a directory\e[0m", 2);
	else if (error_code == MISS_TEXT)
		ft_putendl_fd("> Texture's path is missing\e[0m", 2);
	else if (error_code == MISS_COLOR)
		ft_putendl_fd("> Color information about floor or ceilling is missing\e[0m", 2);
	else if (error_code == INEXISTANT)
		ft_putendl_fd("> Texture's path doesn't exist\e[0m", 2);
	else if (error_code == TEXT_EXTENSION)
		ft_putendl_fd("> Texture's extension must be *.xpm\e[0m", 2);
}

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
		ft_putendl_fd("> Cannot open this file or doesn't exist\e[0m", 2);
	else if (error_code == EMPTY_LINE)
		ft_putendl_fd("> An empty line has been found in the map\e[0m", 2);
	else if (error_code == INVALID)
		ft_putendl_fd("> An invalid symbol/format has been detected\e[0m", 2);
	else if (error_code == RANGE_RGB)
		ft_putendl_fd("> RGB color's range must be between 0 and 255\e[0m", 2);
	else if (error_code == EDGES)
		ft_putendl_fd("> The maze must be closed by walls\e[0m", 2);
	else if (error_code == NO_MAP)
		ft_putendl_fd("> No map has been found in the file\e[0m", 2);
	else if (error_code == PLAYER)
		ft_putendl_fd("> More than one player has been detected\e[0m", 2);
	else if (error_code == NO_PLAYER)
		ft_putendl_fd("> No player has been found\e[0m", 2);
	map_error_bis(error_code);
	return (KO);
}

int	free_map(t_map *map)
{
	if (!map)
		return (KO);
	map->textures_path = free_double_tab(map->textures_path);
	map->maze = free_double_tab(map->maze);
	return (SUCCESS);
}

char	**free_double_tab(char **map)
{
	int i;

	i = 0;
	if (!map)
		return (NULL);
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
