/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:07:00 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/29 11:38:39 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_filename_validity(char *filename)
{
	int	fd;
	int	len;

	if (!filename)
		return (map_error(ERROR_MAP), KO);
	len = ft_strlen(filename);
	if (filename[len - 1] != 'b' || filename[len - 2] != 'u'
		|| filename[len - 3] != 'c' || filename[len - 4] != '.')
		return (map_error(NAME_MAP));
	fd = open(filename, __O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (map_error(DIRECTORY));
	}
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
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}

int	check_maze_valid_symbol(char *line, bool msg_error)
{
	int	i;

	if (!line)
		return (0);
	if (is_line_empty(line))
	{
		if (msg_error)
			map_error(EMPTY_LINE);
		return (0);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && line[i] != '\n' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
			&& !(line[i] >= '0' && line[i] <= '5'))
		{
			if (msg_error)
				map_error(INVALID);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_map_borders_edges(char **maze, char *line, int index)
{
	int	i;

	if (!maze || !line)
		return (map_error(ERROR_MAP));
	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != 32)
			return (KO);
		i++;
	}
	if (!line[i] && index - 1 > 0 && maze[index - 1][i]
		&& (maze[index - 1][i] == '0' 
		|| maze[index - 1][i] == 'N' || maze[index - 1][i] == 'S'
		|| maze[index - 1][i] == 'W' || maze[index - 1][i] == 'E'))
		return (KO);
	return (SUCCESS);
}

int	check_maze_edges(char **maze, char *line, int index, int height)
{
	int	i;
	int	len;

	if (!line || !maze)
		return (KO);
	if ((index == 0 || index == (height - 1)))
		return (check_map_borders_edges(maze, line, index));
	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	len = ft_strlen(line) - 2;
	if (line[i] != '1' || line[len] != '1')
		return (KO);
	while (line[i])
	{
		if (!line[i] && maze[index - 1][i] && (maze[index - 1][i] == '0'
			|| maze[index - 1][i] == 'N' || maze[index - 1][i] == 'S'
			|| maze[index - 1][i] == 'W' || maze[index - 1][i] == 'E'))
			return (KO);
		i++;
	}
	return (SUCCESS);
}
