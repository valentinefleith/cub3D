/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:11:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/25 10:39:43 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

# define MISSING_MAP 0
# define ERROR_MAP 2 // General error like a NULL pointer
# define NAME_MAP 3
# define FILE_MAP 4

# define EMPTY_LINE 5
# define DOUBLE_SYMB 6
# define INVALID 7
# define RANGE_RGB 8

typedef struct s_map t_map;

/* map_init.c */

int		init_map(int args, char *filename, t_map *map);
int		check_filename_validity(char *filename);
char	**init_tab(int len);
int		is_line_empty(char *line);

/* map_parsing.c */

int		parsing_env_map_data(char *filename, t_map *map);
int		parsing_textures_path(char *line, t_map *map);
int		parsing_colors(char *line, t_map *map);
int		find_color(char *line);
int		check_color_symbol(char *line);

/* parsing_maze.c */

int		store_the_maze(int fd, char **map);
int		check_maze_valid_symbol(char *line);
int		get_maze_size(int fd, char *prev_line);
char	*skip_beginning(int fd);

/* map_security.c */

int		map_error(int error_code);
int		free_map(t_map *map);
char	**free_double_tab(char **map);
char	**free_path(char **tab);

#endif
