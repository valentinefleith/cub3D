#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

typedef struct s_point t_point;
typedef struct s_maze t_maze;

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

/* DRAW WALL *****************************************************************/

void		draw_wall(t_maze *maze, t_img texture, double wall_height, int x);
void		draw_floor(t_maze *maze, int x, int start);
void		draw_ceilling(t_maze *maze, int x, int end);
int			get_px_color(t_img texture, int x, int y);

/* IMAGE *********************************************************************/

t_img		init_img_struct(void);
int			render_one_frame(t_maze *game, bool init);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* TEXTURE *******************************************************************/

int			init_textures(t_maze *game);
t_img		setup_texture(t_maze *game, t_vector wall_point, double angle);

/* MINIMAP *******************************************************************/

void		draw_rectangle(t_maze *maze, t_point center_pos, int width,
			int height, int color);
void		draw_line(t_maze *maze, t_point start, t_point end, int color);
void		draw_line_from_angle(t_maze *maze, t_point point, double angle,
			int size, int color);
void 		draw_grid(t_maze *maze);
#endif