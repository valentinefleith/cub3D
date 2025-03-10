/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:11:30 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/12 10:34:09 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "parsing.h"
# include "keycodes.h"
# include "colors.h"
# include "raycasting.h"
# include "rendering.h"

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>

// # define SUCCESS 0 // if cause problem and KO 1
# define SUCCESS 1
# define KO 0
# define MLX_ERROR 2

# define _USE_MATH_DEFINES

# define HEIGHT 880
# define WIDTH 1000
# define TILE_SIZE 30.0

// # define PLAYER_RADIUS (TILE_SIZE / 3)
# define PLAYER_RADIUS 5.0
# define ROTATION_SPEED 0.025
# define PLAYER_SPEED 1

# define FOV 60.0
# define FOV_RADIANS 1.0472
// # define FOV_RADIANS ((FOV) * M_PI) / 180.0

typedef enum e_direction t_dir;
typedef enum e_orientation t_orient;
typedef enum e_key t_key;
// typedef struct s_map t_map;
typedef struct s_img t_img;

typedef struct s_map
{
	char		**maze;
	int			width;
	int			height;
	uint32_t	floor_color;
	uint32_t	ceilling_color;	
	char		**textures_path;
}				t_map;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	double		looking_angle;
	t_vector	pos;
	bool		keys_pressed[6];
}				t_player;

typedef struct s_maze
{
	void		*mlx;
	void		*win;
	t_img 		img;
	t_img 		texture[4];
	t_img		minimap;
	t_player	player;
	t_map		map;
	double		plane_distance;
	bool		minimap_key;
	bool		horizontal_point;
}				t_maze;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

int				game_loop(t_maze *game);

/* CONTROL *******************************************************************/

void			print_game_struct(t_maze *game);

// Initialization
t_maze			game_initialization(void);
t_map			init_map_struct(void);
t_player		init_player_struct(void);
char			**init_tab(int len);
t_img			init_img_struct(void);

// Exit
int 			free_window(t_maze* maze);
int				exit_program(t_maze *maze, int error_code);
int				drestroy_textures_img(t_maze *game);

// Key events
int				key_press(int keycode, t_maze *game);
int				key_release(int keycode, t_maze *game);

// Move
int				update_player_pos(t_maze *game);

#endif
