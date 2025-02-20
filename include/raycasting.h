#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"
# include <stdbool.h>


typedef enum e_direction
{
	up,
	down,
	left,
	right
}			t_dir;

typedef struct s_maze t_maze;
typedef struct s_map t_map;
typedef struct s_position t_position;

/* RAYCASTING ****************************************************************/

void		raycasting(t_maze *maze);
int			find_wall_distance(t_maze *maze, double angle);
bool		is_wall_point(t_map *map, t_position point);
int			compute_distance(t_position a, t_position b);
int			get_smallest_distance(t_position target, t_position a, t_position b);

/* GET DIRECTION *************************************************************/

t_dir		get_vertical_direction(double angle);
t_dir		get_horizontal_direction(double angle);

/* GET POINT *****************************************************************/

t_position	get_first_y_point(t_position player, double angle, t_dir direction);
t_position	get_first_x_point(t_position player_pos, double angle, t_dir direction);
t_position	get_wall_point_horizon(t_maze *maze, t_map *map, double angle, t_dir direction, t_position point);// proto to debug
// t_position get_wall_point_horizon(t_map *map, double angle, t_dir direction, t_position point);
t_position	get_wall_point_vert(t_maze *maze, t_map *map, double angle, t_dir direction, t_position point);//proto to debug
// t_position	get_wall_point_vert(t_map *map, double angle, t_dir direction, t_position point);

/* UTILS *********************************************************************/

double		normalize_angle(double angle);
void		draw_fov(t_maze *maze);

#endif