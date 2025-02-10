/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:11:30 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 22:19:39 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "keycodes.h"
# include "colors.h"
# include "player.h"

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define SUCCESS 0
#define MLX_ERROR 1
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
	t_player player;
}				t_maze;

//typedef struct s_pixel {
	//int x;
	//int y;
//}			t_pixel;



int render_one_frame(t_maze *maze, bool initialization);
void init_hook(t_maze *maze);
void init_player_pos(t_maze* maze);
int free_window(t_maze* maze);
int exit_program(t_maze *maze);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void raycasting(t_maze *maze);
int key_events(int keycode, t_maze *maze);

#endif
