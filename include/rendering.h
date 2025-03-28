/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:30:04 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 18:30:33 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

typedef struct s_point	t_point;
typedef struct s_maze	t_maze;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	double	x;
	double	y;
}			t_img;

typedef struct s_minimap
{
	t_img	map;
	int		width;
	int		height;
	int		cell_size;
}			t_minimap;

typedef struct s_rectangle_characteristics
{
	int	height;
	int	width;
	int	color;
}			t_rectangle_characteristics;

typedef struct s_line_characteristics
{
	double	angle;
	double	size;
	int		color;
}			t_line_characteristics;

/* DRAW WALL *****************************************************************/

void						draw_wall(t_maze *maze, t_img texture,
								double wall_height, int x);
void						draw_floor(t_maze *maze, int x, int start);
void						draw_ceilling(t_maze *maze, int x, int end);

/* IMAGE *********************************************************************/

int							get_px_color(t_img texture, int x, int y);
void						my_mlx_pixel_put(t_img *img, int x, int y,
								int color);
t_img						init_img_struct(void);
int							render_one_frame(t_maze *game, bool init);

/* TEXTURE *******************************************************************/

int							init_textures(t_maze *game);
t_img						setup_texture(t_maze *game, t_vector wall_point,
								double angle);

/* MINIMAP *******************************************************************/

int							minimap(t_maze *game);
void						draw_minimap(t_maze *game);
void						draw_player(t_maze *game);
void						draw_rectangle(t_maze *maze, t_point center_pos,
								t_rectangle_characteristics characteristics);
void						draw_line(t_maze *maze, t_point start, t_point end,
								int color);
void						draw_line_from_angle(t_maze *maze, t_point point,
								t_line_characteristics characteristics);
void						draw_grid(t_maze *maze);
t_rectangle_characteristics	to_rectangle_characteristics(int height,
								int width, int color);
t_line_characteristics		to_line_characteristics(double angle,
								double size, int color);

#endif