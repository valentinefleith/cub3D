#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

typedef struct s_vector t_vector;
typedef struct s_maze t_maze;

typedef struct s_raycast
{
	t_vector	plane;
	t_vector	view_dir;
	t_vector	camera;
	t_vector	player;
	t_vector	ray;
	t_vector	step_size;
	t_vector	step_orientation;
	t_vector	delta_dist;
}				t_raycast;

/* RAYCASTING ****************************************************************/

void		raycasting(t_maze *game, int map_w, t_vector player);
void		update_raycast(t_raycast *rc, int x, int width);
int			find_wall(t_raycast *rc, char **maze, t_vector *map);
t_raycast 	init_raycasting(void);

/* UPDATE STEPS **************************************************************/

void		increment_step(t_raycast *rc, t_vector player, t_vector map);
void		update_negative_step(t_raycast *rc, int player, int cell_px, char coordinates);
void		update_positive_step(t_raycast *rc, int player, int cell_px, char coordinates);


#endif