/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:00:55 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/11 20:26:02 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
# include "player.h"


// For now, position's hardcoded
// t_player	init_player(int map_pos_x, int map_pos_y)
// {
// 	t_player	player;

// 	player.pos.x = map_pos_x * TILE_SIZE + TILE_SIZE / 2;
// 	player.pos.y = map_pos_y * TILE_SIZE + TILE_SIZE / 2;
// 	player.angle = M_PI; // means player's view direction initially faces the WEST
// 	player.fov_rd = (FOV * M_PI) / 180; // convert from degrees to radians.
// 	return (player);
// }
