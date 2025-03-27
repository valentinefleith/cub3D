#include "cub3d.h"

/* Adding error mesage if there is doors in the map but no color sequence and vice versa.
But also if there is no walls 3,4,5 */
int	parsing_map_file(int args, char *filename, t_map *map, t_player *player)
{
	int	fd;

	if (args != 2)
		return (map_error(MISSING_MAP));
	if (check_filename_validity(filename))
	{
		if (parsing_env_map_data(filename, map))
		{
			if (map->height == -1)
				return (KO);
			fd = open(filename, O_RDONLY);
			if (fd != -1)
			{
				map->maze = init_tab(map->height);
				if (!map->maze)
					return (map_error(ERROR_MAP));
				if (maze_parsing(fd, map->maze, map->height, map->width))
					return (parsing_player(map->maze, player));
				return (free_map(map), KO);
			}
			return (map_error(FILE_MAP));
		}
		return (KO);
	}
	return (KO);
}

int	parsing_env_map_data(char *filename, t_map *map)
{
	int		fd;
	char	*line;

	if (!filename || !map || !map->textures_path)
		return (map_error(ERROR_MAP), KO);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (map_error(FILE_MAP));
	line = read_file(fd);
	while (line && !check_maze_valid_symbol(line, false))
	{
		if (!is_line_empty(line))
		{
			if (!parsing_textures_path(line, map)) // assign texture's path in map's struct
			{
				if (!parsing_colors(line, map))  // assign RGB colors in map's struct
					return (free(line), close(fd), map_error(INVALID));
			}
		}
		free(line);
		line = read_file(fd);
	}
	map->height = get_maze_size(fd, line, &map->width);
	return (close(fd), free(line), SUCCESS);
}
