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
# define EMPTY_MAP 5

typedef struct s_map t_map;
// typedef struct s_map
// {
// 	char	**map;
//	char	start_dir;
// 	int		p_x;
// 	int		p_y;
// 	int		map_w;
// 	int		map_h;
// }			t_map;

int		init_map(int args, char *filename, t_map *map);
int		check_filename_validity(char *filename);
int		map_error(int error_code);
char	**map_parsing(char *map_file, t_map *data);
int		check_map_valid_symbol(char *line);
char	**free_map(char **map);
int		get_map_size(char *filename);
char	**store_the_map(char *filename, char **map);

#endif
