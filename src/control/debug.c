/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:54:39 by luvallee          #+#    #+#             */
/*   Updated: 2025/03/27 15:55:13 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_img_struct(t_img img, char *name)
{
	if (name)
		printf("game->%s -> \n", name);
	if (img.img)
		printf("%s.img != NULL\n", name);
	else
		printf("%s.img == NULL\n", name);
	if (img.addr)
		printf("%s.img != NULL\n", name);
	else
		printf("%s.img == NULL\n", name);
	printf("%s.bits_per_pixel == %d\n", name, img.bits_per_pixel);
	printf("%s.line_length == %d\n", name, img.line_length);
	printf("%s.endian == %d\n", name, img.endian);
	printf("%s.width == %d\n", name, img.width);
	printf("%s.height == %d\n", name, img.height);
	printf("%s.x == %f\n", name, img.x);
	printf("%s.y == %f\n", name, img.y);
}

static void	print_player_struct(t_player player)
{
	printf("game->player -> \n");
	printf("player.looking_angle == %f\n", player.looking_angle);
	printf("player.pos.x == %f\n", player.pos.x);
	printf("player.pos.y == %f\n", player.pos.y);
}

static void	print_map_struct(t_map map)
{
	int	i;

	printf("game->map -> \n");
	printf("map.width == %d\n", map.width);
	printf("map.height == %d\n", map.height);
	printf("map.floor_color == %d\n", map.floor_color);
	printf("map.ceilling_color == %d\n", map.ceilling_color);
	i = 0;
	while (i < 4)
	{
		if (map.textures_path[i])
			printf("map.textures_path[%d] == %s\n", i, map.textures_path[i]);
		else
			printf("map.textures_path[%d] == NULL\n", i);
		i++;
	}
	i = 0;
	while (map.maze[i])
	{
		printf("%s\n", map.maze[i]);
		i++;
	}
}

static void	print_textures_tab(t_maze *game, char *name)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("[%d] ", i);
		print_img_struct(game->texture[i], name);
		i++;
	}
}

void	print_game_struct(t_maze *game)
{
	if (!game)
	{
		printf("t_maze *game == NULL\n");
		return ;
	}
	if (game->mlx)
		printf("game->mlx != NULL\n");
	else
		printf("game->mlx == NULL\n");
	if (game->win)
		printf("game->win != NULL\n");
	else
		printf("game->win == NULL\n");
	if (game->mlx)
		printf("game->mlx != NULL\n");
	else
		printf("game->mlx == NULL\n");
	printf("************************************************************\n");
	print_img_struct(game->img, "img");
	printf("************************************************************\n");
	print_player_struct(game->player);
	printf("************************************************************\n");
	print_map_struct(game->map);
	printf("************************************************************\n");
	print_textures_tab(game, "textures");
}
