/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:06:18 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 16:20:01 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_H
# define CONTROL_H

# include "cub3d.h"

/* DEBUG *********************************************************************/

void		print_game_struct(t_maze *game);

/* Initialization ************************************************************/

t_maze		game_initialization(void);
t_map		init_map_struct(void);
t_player	init_player_struct(void);
char		**init_tab(int len);
t_img		init_img_struct(void);

/* EXIT **********************************************************************/

int			free_window(t_maze *maze);
int			exit_program(t_maze *maze, int error_code);
int			drestroy_textures_img(t_maze *game);

/* KEY EVENT *****************************************************************/

int			key_press(int keycode, t_maze *game);
int			key_release(int keycode, t_maze *game);
int			mouse_move(int x, int y, t_maze *game);

/* MOVE **********************************************************************/

int			update_player_pos(t_maze *game);
int			rotate_player(t_maze *game, int key_pressed);

/* DOOR **********************************************************************/

int			puzzle_game(t_maze *game, char **maze);
int			handle_sequence_color(t_maze *game, char wall_type);
int			handle_door(t_maze *game, t_map *map, t_point pos);
int			draw_picked_color(t_maze *game);

#endif
