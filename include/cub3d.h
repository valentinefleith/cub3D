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
# include "map.h"
# include "keycodes.h"
# include "colors.h"
# include "player.h"
# include "raycasting.h"

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define SUCCESS 0
# define KO 1
# define MLX_ERROR 2

# define HEIGHT 880
# define WIDTH 880


# define _USE_MATH_DEFINES
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4

# define FOV 60
# define FOV_RADIANS 1.0472
// # define FOV_RADIANS (FOV * M_PI) / 180

#define TILE_SIZE 64

typedef struct s_vector
{
	double x;
	double y;
}			t_vector;

typedef struct s_player
{
	t_vector	pos;
	double		looking_angle;
	// RAJOUTER PLUS TARD: angle de vue etc.
}		t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	double		x;
	double		y;
	int			orientation;
	int			*textures[4];
}				t_img;

typedef struct s_dimensions
{
	int			height;
	int			width;
} t_dimensions;

typedef struct s_map
{
	char		**maze;
	// player's start direction (N,S,W,E)
	char		start_dir;
	// player's coordinates
	int			p_x;
	int			p_y;
	// maze's size
	t_dimensions dimensions;
	// colors in RGB and path for wall's textures
	int			floor[3];
	int			celling[3];
	char		**textures_path;
}				t_map;

typedef struct s_maze
{
	void		*mlx;
	void		*win;
	t_img 		img;
	t_player	player;
	t_map		*map;
	int			plane_distance;
}				t_maze;

typedef struct s_point
{
	int			x;
	int			y;
}			t_point;

void	setup_texture(t_maze *maze, t_vector wall_point, double wall_height, int y, int x);
void	draw_wall(t_maze *maze, t_vector wall_point, double wall_height, int x);
// void	draw_wall(t_maze *maze, double wall_height, int slice);
int render_one_frame(t_maze *maze, bool initialization);
void init_hook(t_maze *maze);
void init_player_pos(t_maze* maze);
int free_window(t_maze* maze);
int exit_program(t_maze *maze);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
// void raycasting(t_maze *maze);
int key_events(int keycode, t_maze *maze);


/* DEBUG must delete later */
void		debug_textures_path(char **tab);
void 		debug_colors(int floor[3], int ceilling[3]);




void	draw_rectangle(t_maze *maze, t_position center_pos, int width,
		int height, int color);
void	draw_line(t_maze *maze, t_position start, t_position end, int color);
void	draw_line_from_angle(t_maze *maze, t_position point, double angle,
		int size, int color);
void draw_grid(t_maze *maze);


#endif
