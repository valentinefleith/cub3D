/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:03:36 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 16:06:39 by luvallee         ###   ########.fr       */
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
# include <sys/time.h>

# define SUCCESS 1
# define KO 0
# define MLX_ERROR 2

# define _USE_MATH_DEFINES

# define HEIGHT 880
# define WIDTH 1000
# define TILE_SIZE 30.0
# define MINI_TILE 15.0

# define PLAYER_RADIUS 5.0
# define ROTATION_SPEED 0.025
# define PLAYER_SPEED 1.7

# define FOV 60.0
# define FOV_RADIANS 1.0472

# define TEXTURE_NB 5

typedef enum e_direction	t_dir;
typedef enum e_orientation	t_orient;
typedef enum e_key			t_key;
typedef struct s_img		t_img;

typedef struct s_map
{
	char		**maze;
	int			width;
	int			height;
	uint32_t	floor_color;
	uint32_t	ceilling_color;
	uint32_t	*color_sequence;
	uint32_t	target_color;
	uint32_t	color_picked;
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
	bool		keys_pressed[7];
}				t_player;

typedef struct s_maze
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		texture[TEXTURE_NB];
	t_img		minimap;
	t_player	player;
	t_map		map;
	double		plane_distance;
	bool		minimap_key;
	bool		horizontal_point;
	int			wall_type;
}				t_maze;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

int				game_loop(t_maze *game);

#endif
