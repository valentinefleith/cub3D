/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:39:58 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 15:43:06 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_file(int fd)
{
	char	*line;

	if (fd == -1)
		return (map_error(FILE_MAP), NULL);
	line = get_next_line(fd);
	return (line);
}

char	*skip_beginning(int fd)
{
	char	*line;

	line = NULL;
	while (!check_maze_valid_symbol(line, false))
	{
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	get_maze_size(int fd, char *prev_line, int *width)
{
	int		height;
	int		current_width;
	char	*line;

	if (!prev_line)
		return (map_error(NO_MAP), -1);
	height = -1;
	if (check_maze_valid_symbol(prev_line, false))
		height = 1;
	line = NULL;
	current_width = ft_strlen(prev_line) - 1;
	while (1)
	{
		if (line && check_maze_valid_symbol(line, false))
			height++;
		if (current_width > *width)
			*width = current_width;
		free(line);
		line = get_next_line(fd);
		if (!line)
			return (close(fd), height);
		current_width = ft_strlen(line) - 1;
	}
	return (close(fd), height);
}

void	remove_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 32)
			line[i] = '1';
		i++;
	}
}

char	*resize_line_with_walls(char *line, int width)
{
	char	*new_line;
	int		len;
	int		i;

	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * (len + (width - len) + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i] && i < (len - 1))
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new_line[i] = '1';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}
