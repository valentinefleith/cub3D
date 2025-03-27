/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:44:44 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 15:47:16 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_maze *game)
{
	int		i;

	if (!game || !game->mlx)
		return (KO);
	i = 0;
	while (game->map.textures_path[i])
	{
		if (!game->map.textures_path[i] && i != 4)
			return (map_error(MISS_TEXT));
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx, \
			game->map.textures_path[i], &game->texture[i].width, \
			&game->texture[i].height);
		if (!game->texture[i].img)
			return (map_error(INEXISTANT));
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, \
			&game->texture[i].bits_per_pixel, &game->texture[i].line_length, \
			&game->texture[i].endian);
		if (!game->texture[i].addr)
			return (map_error(ERROR_MAP));
		i++;
	}
	game->map.target_color = get_px_color(game->texture[0], \
		game->texture[0].width / 2, game->texture[0].height / 2);
	return (SUCCESS);
}

static bool	check_texture_extension(char *texture)
{
	int	len;

	len = ft_strlen(texture);
	if (texture[len - 1] != 'm' || texture[len - 2] != 'p'
		|| texture[len - 3] != 'x' || texture[len - 4] != '.')
		return (false);
	return (true);
}

int	get_texture_cell(char *line)
{
	if (!ft_strncmp(line, "NO ./", 5))
		return (0);
	else if (!ft_strncmp(line, "SO ./", 5))
		return (1);
	else if (!ft_strncmp(line, "WE ./", 5))
		return (2);
	else if (!ft_strncmp(line, "EA ./", 5))
		return (3);
	else if (!ft_strncmp(line, "DO ./", 5))
		return (4);
	return (-1);
}

int	parsing_textures_path(char *line, t_map *map)
{
	int	cell;

	if (!line || !map)
		return (map_error(ERROR_MAP), 0);
	cell = get_texture_cell(line);
	if (cell != -1)
	{
		if (map->textures_path[cell])
			return (map_error(DOUBLE_SYMB));
		map->textures_path[cell] = ft_substr(line, 5, ft_strlen(line) - 6);
		if (!map->textures_path[cell])
			return (map_error(ERROR_MAP));
		if (!check_texture_extension(map->textures_path[cell]))
			return (map_error(TEXT_EXTENSION));
		return (SUCCESS);
	}
	return (KO);
}
