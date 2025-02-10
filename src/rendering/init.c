/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:28:56 by vafleith          #+#    #+#             */
/*   Updated: 2025/02/10 22:17:17 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_hook(t_maze *maze) {
	mlx_hook(maze->win, 17, 0, exit_program, maze);
	mlx_key_hook(maze->win, key_events, maze);
}
