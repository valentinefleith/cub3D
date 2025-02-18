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

# define HEIGHT 960
# define WIDTH 960
# define FOV 66

typedef struct s_raycast t_raycast;
typedef struct s_map t_map;
typedef struct s_size t_size;
typedef struct s_vector t_vector;


// typedef struct s_vector
// {
// 	double			x;
// 	double			y;
// }				t_vector;

// typedef struct s_player
// {
// 	t_vector	pos; // x,y coordinates in pixels
// 	double		angle;
// 	float		fov_rd;
// }				t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_maze {
	void		*mlx;
	void		*win;
	t_img 		img;
	t_vector	player;
	t_map		*map;
	t_raycast	*rc;
}				t_maze;

void	draw(t_maze *game, t_raycast *rc, int x, int wall_orientation);
void	draw_wall(t_maze *game, int x, int y_start, int y_end, int color);
void	draw_ceilling(t_maze *game, int x, int y_end);
void	draw_floor(t_maze *game, int x, int y_start);


int render_one_frame(t_maze *maze, bool initialization);
void init_hook(t_maze *maze);
// void init_player_pos(t_maze* maze);
// t_player	init_player(int map_pos_x, int map_pos_y);
int free_window(t_maze* maze);
int exit_program(t_maze *maze);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
// void raycasting(t_maze *maze);
int key_events(int keycode, t_maze *maze);



// void	draw_rectangle(t_maze *maze, t_position center_pos, int width,
// 		int height, int color);
// void	draw_line(t_maze *maze, t_position start, t_position end, int color);
// void	draw_line_from_angle(t_maze *maze, t_position point, double angle,
// 		int size, int color);


#endif
