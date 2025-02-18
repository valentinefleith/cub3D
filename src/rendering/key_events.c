/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:17:35 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/11 21:34:15 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int move_player(t_maze *maze, int keycode) {
// 	if (keycode == XK_d)
// 		maze->player.x += PLAYER_MOVE_PX;
// 	else if (keycode == XK_a)
// 		maze->player.x -= PLAYER_MOVE_PX;
// 	else if (keycode == XK_w)
// 		maze->player.y -= PLAYER_MOVE_PX;
// 	else if (keycode == XK_s)
// 		maze->player.y += PLAYER_MOVE_PX;
// 	render_one_frame(maze, false);
// 	return SUCCESS;
// }

// static int rotate_player(t_maze *maze, int keycode) {
// 	if (keycode == XK_Left)
// 		maze->player.looking_angle += 0.1;
// 	else
// 		maze->player.looking_angle -= 0.1;
// 	render_one_frame(maze, false);
// 	return SUCCESS;
// }

static int move_player(t_maze *maze, int keycode)
{
	double	old_view_dir_x;
	double	old_plane_x;

	old_view_dir_x = maze->rc->view_dir.x;
	old_plane_x = maze->rc->plane.x;
	if (keycode == XK_d)
	{
		maze->rc->view_dir.x = maze->rc->view_dir.x * cos(-0.1) - maze->rc->view_dir.y * sin(-0.1);
		maze->rc->view_dir.y = old_view_dir_x * sin(-0.1) + maze->rc->view_dir.y * cos(-0.1);
		maze->rc->plane.x = old_plane_x * cos(-0.1) - maze->rc->plane.y * sin(-0.1);
		maze->rc->plane.y = old_plane_x * sin(-0.1) + maze->rc->plane.y * cos(-0.1);
	}
	else if (keycode == XK_a)
	{
		maze->rc->view_dir.x = maze->rc->view_dir.x * cos(0.1) - maze->rc->view_dir.y * sin(0.1);
		maze->rc->view_dir.y = old_view_dir_x * sin(0.1) + maze->rc->view_dir.y * cos(0.1);
		maze->rc->plane.x = maze->rc->plane.x * cos(0.1) - maze->rc->plane.y * sin(0.1);
		maze->rc->plane.y = old_plane_x * sin(0.1) + maze->rc->plane.y * cos(0.1);
	}
	else if (keycode == XK_w)
	{
		maze->rc->player.x += maze->rc->view_dir.x * 0.1;
		maze->rc->player.y += maze->rc->view_dir.y * 0.1;
	}
	else if (keycode == XK_s)
	{
		maze->rc->player.x -= maze->rc->view_dir.x * 0.1;
		maze->rc->player.y -= maze->rc->view_dir.y * 0.1;
	}
	render_one_frame(maze, false);
	return SUCCESS;
}

int key_events(int keycode, t_maze *maze) {
	if (keycode == XK_s || keycode == XK_w || keycode == XK_a || keycode == XK_d)
		return (move_player(maze, keycode));
	// if (keycode == XK_Right || keycode == XK_Left)
	// 	return (rotate_player(maze, keycode));
	return 0;
}
