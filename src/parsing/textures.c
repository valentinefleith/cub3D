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
			return (KO);
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx, game->map.textures_path[i], &game->texture[i].width, &game->texture[i].height);
		if (!game->texture[i].img)
			return (KO); // TODO : add error msg
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, &game->texture[i].bits_per_pixel, &game->texture[i].line_length, &game->texture[i].endian);
		if (!game->texture[i].addr)
			return (KO);
		i++;
	}
	return (SUCCESS);
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
		if (map->textures_path[cell]) // means that's already assigned = data en doublon
			return (map_error(DOUBLE_SYMB), 0);
		map->textures_path[cell] = ft_substr(line, 5, ft_strlen(line) - 6);
		if (!map->textures_path[cell])
			return (0);
		return (1);
	}
	return (0);
}
