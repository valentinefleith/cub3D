/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:11:30 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/25 10:39:43 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "map.h"
# include "keycodes.h"

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define SUCCESS 0
# define KO 1
# define MLX_ERROR 2

# define HEIGHT 960
# define WIDTH 1080

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_maze {
	void *mlx;
	void *win;
	t_img img;
}				t_maze;

typedef struct s_map
{
	char	**maze;
	// player's start direction (N,S,W,E)
	char	start_dir;
	// player's coordinates
	int		p_x;
	int		p_y;
	// maze's size
	int		heigth;
	int		width;
	// colors in RGB and path for wall's textures
	int		floor[3];
	int		celling[3];
	char	**textures_path;
}			t_map;

/* DEBUG must delete later */
void		debug_textures_path(char **tab);
void 		debug_colors(int floor[3], int ceilling[3]);

#endif
