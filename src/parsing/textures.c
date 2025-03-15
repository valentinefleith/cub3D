# include "cub3d.h"

int	init_textures(t_maze *game)
{
	int		i;

	if (!game || !game->mlx)
		return (KO);
	i = 0;
	while (i < 4)
	{
		if (!game->map.textures_path[i])
			return (map_error(MISS_TEXT));
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx, game->map.textures_path[i], &game->texture[i].width, &game->texture[i].height);
		if (!game->texture[i].img)
			return (map_error(INEXISTANT));
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, &game->texture[i].bits_per_pixel, &game->texture[i].line_length, &game->texture[i].endian);
		if (!game->texture[i].addr)
			return (map_error(ERROR_MAP));
		i++;
	}
	return (SUCCESS);
}

int	init_sprite(t_maze *game)
{
	if (!game || game->mlx)
		return (KO);
	game->sprite.img = mlx_xpm_file_to_image(game->mlx, game->map.sprite, &game->sprite.width, &game->sprite.height);
	if (!game->sprite.img)
		return (map_error(INEXISTANT));
	game->sprite.addr = mlx_get_data_addr(game->sprite.img, &game->sprite.bits_per_pixel, &game->sprite.line_length, &game->sprite.endian);
	if (!game->sprite.addr)
		return (map_error(ERROR_MAP));
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

int	parsing_textures_path(char *line, t_map *map)
{
	int	cell;

	if (!line || !map)
		return (map_error(ERROR_MAP), 0);
	cell = -1;
	if (!ft_strncmp(line, "NO ./", 5))
		cell = 0;
	else if (!ft_strncmp(line, "SO ./", 5))
		cell = 1;
	else if (!ft_strncmp(line, "WE ./", 5))
		cell = 2;
	else if (!ft_strncmp(line, "EA ./", 5))
		cell = 3;
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
	return (parsing_sprites(line, map));
}

int	parsing_sprites(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO ./", 5))
	{
		if (map->sprite)
			return (map_error(DOUBLE_SYMB));
		map->sprite = ft_substr(line, 5, ft_strlen(line) - 6);
		if (!map->sprite)
			return (map_error(ERROR_MAP));
		return (SUCCESS);
	}
	return (KO);
}