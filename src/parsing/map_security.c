/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_security.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:33:04 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 15:37:37 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_error_bis(int error_code)
{
	if (error_code == DOUBLE_SYMB)
		ft_putendl_fd("> Multiple lines concern the same symbol/data\e[0m", 2);
	else if (error_code == DIRECTORY)
		ft_putendl_fd("> The map file is a directory\e[0m", 2);
	else if (error_code == NO_MAP)
		ft_putendl_fd("> No map has been found in the file\e[0m", 2);
	else if (error_code == MISS_TEXT)
		ft_putendl_fd("> Texture's path is missing\e[0m", 2);
	else if (error_code == MISS_COLOR)
		ft_putendl_fd("> Color code for floor or ceilling is missing\e[0m", 2);
	else if (error_code == INEXISTANT)
		ft_putendl_fd("> Texture's path doesn't exist\e[0m", 2);
	else if (error_code == TEXT_EXTENSION)
		ft_putendl_fd("> Texture's extension must be *.xpm\e[0m", 2);
	else if (error_code == MISS_PUZZLE)
		ft_putendl_fd("> Incomplete info to start door puzzle\e[0m", 2);
	else if (error_code == MISS_ENV)
		ft_putendl_fd("> Incomplete info to start the game\e[0m", 2);
	else if (error_code == PLAYER)
		ft_putendl_fd("> More than one player has been detected\e[0m", 2);
	else if (error_code == NO_PLAYER)
		ft_putendl_fd("> No player has been found\e[0m", 2);
}

int	map_error(int error_code)
{
	static bool	prev_error = false;

	if (prev_error)
		return (KO);
	prev_error = true;
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
		ft_putendl_fd("> Empty line has been found in/after the map\e[0m", 2);
	else if (error_code == INVALID)
		ft_putendl_fd("> An invalid symbol/format has been detected\e[0m", 2);
	else if (error_code == RANGE_RGB)
		ft_putendl_fd("> RGB color's range must be between 0 and 255\e[0m", 2);
	else if (error_code == EDGES)
		ft_putendl_fd("> The maze must be closed by walls\e[0m", 2);
	else
		map_error_bis(error_code);
	return (KO);
}

int	free_map(t_map *map)
{
	if (!map)
		return (KO);
	if (map->color_sequence)
		free(map->color_sequence);
	if (map->textures_path[0])
		free(map->textures_path[0]);
	if (map->textures_path[1])
		free(map->textures_path[1]);
	if (map->textures_path[2])
		free(map->textures_path[2]);
	if (map->textures_path[3])
		free(map->textures_path[3]);
	if (map->textures_path[4])
		free(map->textures_path[4]);
	if (map->textures_path)
		free(map->textures_path);
	map->maze = free_double_tab(map->maze);
	return (SUCCESS);
}

char	**free_double_tab(char **map)
{
	int	i;

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

int	clean_maze_parsing(char *line, int fd)
{
	if (line)
		free(line);
	close(fd);
	return (KO);
}
