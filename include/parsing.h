#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"
# include <stdbool.h>

# define MISSING_MAP 0
# define ERROR_MAP 2 // General error like a NULL pointer
# define NAME_MAP 3
# define FILE_MAP 4
# define EMPTY_LINE 5
# define DOUBLE_SYMB 6
# define INVALID 7
# define RANGE_RGB 8
# define EDGES 9
# define NO_MAP 10
# define NO_PLAYER 11
# define PLAYER 12
# define DIRECTORY 13
# define INEXISTANT 14
# define MISS_TEXT 15
# define MISS_COLOR 16
# define TEXT_EXTENSION 17

typedef struct s_map t_map;
typedef struct s_maze t_maze;
typedef struct s_player t_player;

/* PARSING *******************************************************************/

int		parsing_map_file(int args, char *filename, t_map *map, t_player *player);
int		parsing_env_map_data(char *filename, t_map *map);


/* CHECKING ******************************************************************/

int		check_filename_validity(char *filename);
int		is_line_empty(char *line);
int		check_maze_valid_symbol(char *line, bool msg_error);
int		check_map_borders_edges(char *line);
int		check_maze_edges(char *line, int index, int height);

/* MAP_SECURITY **************************************************************/

int		map_error(int error_code);
int		free_map(t_map *map);
char	**free_double_tab(char **map);
char	**free_path(char **tab);

/* COLORS ********************************************************************/

int		parsing_colors(char *line, t_map *map);
int		get_color(char *line, int *i);
char	check_color_symbol(char *line);

/* MAZE **********************************************************************/

int		store_maze(char **maze, int width, char *line, int index);
int		maze_parsing(int fd, char **maze, int height, int width);

/* PLAYER ********************************************************************/

int		parsing_player(char **maze, t_player *player);
char	get_player_spawn(t_player *player, int y, int x, char orientation);


/* TEXTURES ******************************************************************/

int		init_textures(t_maze *game);
int		parsing_textures_path(char *line, t_map *map);

/* UTILS *********************************************************************/

char	*read_file(int fd);
char	*skip_beginning(int fd);
int		get_maze_size(int fd, char *prev_line, int *width);
void	remove_spaces(char *line);
char	*resize_line_with_walls(char *line, int width);

#endif