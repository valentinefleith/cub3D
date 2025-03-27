/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:57:36 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 15:58:45 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	init_img_struct(void)
{
	t_img	img;

	img.img = NULL;
	img.addr = NULL;
	img.bits_per_pixel = 0;
	img.line_length = 0;
	img.endian = 0;
	img.width = 0;
	img.height = 0;
	img.x = 0;
	img.y = 0;
	return (img);
}

char	**init_tab(int len)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = NULL;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

t_player	init_player_struct(void)
{
	t_player	player;
	int			i;

	player.looking_angle = M_PI;
	player.pos.x = 2 * TILE_SIZE + TILE_SIZE / 2;
	player.pos.y = 2 * TILE_SIZE + TILE_SIZE / 2;
	i = 0;
	while (i < 7)
	{
		player.keys_pressed[i] = false;
		i++;
	}
	return (player);
}

t_map	init_map_struct(void)
{
	t_map	map;

	map.maze = NULL;
	map.width = 0;
	map.height = 0;
	map.floor_color = 0;
	map.ceilling_color = 0;
	map.color_sequence = malloc(sizeof(uint32_t) * 4);
	if (!map.color_sequence)
	{
		map_error(ERROR_MAP);
		exit(1);
	}
	map.color_sequence[0] = 0;
	map.color_sequence[1] = 0;
	map.color_sequence[2] = 0;
	map.textures_path = init_tab(TEXTURE_NB);
	map.color_picked = -1;
	map.target_color = -1;
	return (map);
}

t_maze	game_initialization(void)
{
	t_maze	game;
	int		i;

	game.mlx = NULL;
	game.win = NULL;
	game.img = init_img_struct();
	i = 0;
	while (i < TEXTURE_NB)
	{
		game.texture[i] = init_img_struct();
		i++;
	}
	game.minimap = init_img_struct();
	game.player = init_player_struct();
	game.map = init_map_struct();
	game.plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2.0);
	game.minimap_key = false;
	game.horizontal_point = false;
	game.wall_type = 1;
	return (game);
}
