/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:06:41 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 15:37:14 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	parsing_line(char **maze, char *line, int index, int height)
{
	if (!line || is_line_empty(line))
		return (map_error(EMPTY_LINE));
	if (!check_maze_valid_symbol(line, true))
		return (KO);
	if (!check_maze_edges(maze, line, index, height))
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
		if (!parsing_line(maze, line, i, height))
			return (clean_maze_parsing(line, fd));
		if (store_maze(maze, width, line, i))
			i++;
		else
			return (KO);
		free(line);
		line = read_file(fd);
	}
	clean_maze_parsing(line, fd);
	if (!check_puzzle_game_validity(maze))
		return (KO);
	return (SUCCESS);
}

int	check_puzzle_game_validity(char **maze)
{
	int		y;
	int		x;
	int		wall_count;
	int		door_count;

	y = 0;
	wall_count = 0;
	door_count = 0;
	while (maze[y])
	{
		x = 0;
		while (maze[y][x])
		{
			if (maze[y][x] == '2')
				door_count += 1;
			if (maze[y][x] >= '3' && maze[y][x] <= '5')
				wall_count += maze[y][x];
			x++;
		}
		y++;
	}
	if (door_count == 1 && wall_count != ('3' + '4' + '5'))
		return (map_error(MISS_PUZZLE));
	return (SUCCESS);
}
