/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:57:08 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/11 20:26:08 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define PLAYER_WIDTH_PX 10
# define PLAYER_MOVE_PX 15

#include <math.h>

typedef struct s_position {
	int x;
	int y;
}		t_position;

typedef struct s_player {
	t_position pos;
	double looking_angle;
	// RAJOUTER PLUS TARD: angle de vue etc.
}		t_player;



#endif

