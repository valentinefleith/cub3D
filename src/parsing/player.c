/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:00:55 by vafleith          #+#    #+#             */
/*   Updated: 2025/03/27 15:44:11 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_player_spawn(t_player *player, int y, int x, char orientation)
{
	player->pos.x = x * TILE_SIZE + TILE_SIZE / 2;
	player->pos.y = y * TILE_SIZE + TILE_SIZE / 2;
	if (orientation == 'N')
		player->looking_angle = 3 * M_PI / 2;
	if (orientation == 'S')
		player->looking_angle = M_PI / 2;
	if (orientation == 'W')
		player->looking_angle = M_PI;
	if (orientation == 'E')
		player->looking_angle = 0;
	return (orientation);
}

int	parsing_player(char **maze, t_player *player)
{
	int		y;
	int		x;
	char	orientation;

	if (!maze || !player)
		return (map_error(ERROR_MAP));
	y = 0;
	orientation = '\0';
	while (maze[y])
	{
		x = 0;
		while (maze[y][x])
		{
			if ((maze[y][x] == 'N' || maze[y][x] == 'S' || maze[y][x] == 'E'
				|| maze[y][x] == 'W') && orientation == '\0')
				orientation = get_player_spawn(player, y, x, maze[y][x]);
			else if (!(maze[y][x] >= '0' && maze[y][x] <= '5'))
				return (map_error(PLAYER));
			x++;
		}
		y++;
	}
	if (orientation == '\0')
		return (map_error(NO_PLAYER));
	return (SUCCESS);
}
