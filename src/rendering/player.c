/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:00:55 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 22:10:38 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
#include "player.h"

// For now, position's hardcoded

void init_player_pos(t_maze* maze) {
	t_player player;
	t_position player_position;

	player_position.x = WIDTH / 2;
	player_position.y = HEIGHT / 2;

	player.pos = player_position;
	maze->player = player;
}
