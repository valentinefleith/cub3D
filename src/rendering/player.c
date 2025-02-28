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
#include "player.h"

// For now, position's hardcoded

void init_player_pos(t_maze* maze) {
	t_player	player;
	t_vector	player_position;

	player_position.x = 2 * TILE_SIZE + TILE_SIZE / 2;
	player_position.y = 2 * TILE_SIZE + TILE_SIZE / 2;
	// printf("x = %f / y = %f\n", player_position.x, player_position.y);
	player.pos = player_position;
	player.looking_angle = M_PI;
	maze->player = player;
}
