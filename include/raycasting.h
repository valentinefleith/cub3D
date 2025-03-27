/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:28:03 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 18:29:41 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"
# include <stdbool.h>

typedef enum e_direction
{
	facing_up,
	facing_down,
	facing_left,
	facing_right
}			t_dir;

typedef enum e_orientation
{
	north,
	south,
	west,
	east,
}			t_orient;

typedef struct s_maze		t_maze;
typedef struct s_map		t_map;
typedef struct s_position	t_position;
typedef struct s_vector		t_vector;

/* RAYCASTING ****************************************************************/

void		raycasting(t_maze *maze);
t_vector	find_wall_point(t_maze *maze, double angle);
bool		is_wall_point(t_map *map, t_vector point);

/* GET DISTANCE **************************************************************/

double		get_wall_distance(t_vector player_point, t_vector wall_point,
				double player_angle, double current_angle);
double		compute_distance(t_vector a, t_vector b);
t_vector	get_closest_point(t_vector target, t_vector a, t_vector b,
				bool *orientation);

/* GET DIRECTION *************************************************************/

t_dir		get_vertical_direction(double angle);
t_dir		get_horizontal_direction(double angle);

/* GET POINT *****************************************************************/

t_vector	get_first_y_point(t_vector player, double angle, t_dir direction);
t_vector	get_first_x_point(t_vector player_pos, double angle,
				t_dir direction);
t_vector	get_point_horizon(t_map *map, double angle, t_dir direction,
				t_vector point);
t_vector	get_point_vert(t_map *map, double angle, t_dir direction,
				t_vector point);

/* UTILS *********************************************************************/

double		normalize_angle(double angle);

#endif