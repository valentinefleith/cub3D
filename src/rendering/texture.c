#include "cub3d.h"

int	init_textures(t_maze *game)
{
	int		i;

	if (!game)
		return (KO);
	i = 0;
	while (i++ < 4)
		game->texture[i] = init_img_struct();
	i = 0;
	while (i < 4)
	{
		if (!game->map->textures_path[i])
			return (KO);
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx, \
			game->map->textures_path[i], &game->texture[i].width, \
			&game->texture[i].height);
		if (!game->texture[i].img)
			return (KO); // TODO : add error msg
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, \
			&game->texture[i].bits_per_pixel, &game->texture[i].line_length, \
			&game->texture[i].endian);
		if (!game->texture[i].addr)
			return (KO);
		i++;
	}
	return (SUCCESS);
}

static void	setup_x_coord(t_img *texture, t_vector wall_point, bool horizontal_point)
{
	if (horizontal_point) // Point d'intersection du mur etait à l'horizontal
		texture->x = fmodf(wall_point.x * (double)(texture->width / TILE_SIZE), (double)texture->width);
	else
		texture->x = fmodf(wall_point.y * (double)(texture->width / TILE_SIZE), (double)texture->width);
	if (texture->x < 0)
		texture->x += texture->width;
	texture->y = 0;
}

t_img	setup_texture(t_maze *game, t_vector wall_point, double angle)
{
	t_img	texture;

	if (game->horizontal_point)
	{
		if (get_horizontal_direction(angle) == facing_up)
			texture = game->texture[west];
		else
			texture = game->texture[east];
	}
	else
	{
		if (get_vertical_direction(angle) == facing_left)
			texture = game->texture[north];
		else
			texture = game->texture[south];
	}
	// if (!game->horizontal_point && get_horizontal_direction(angle) == facing_up)
	// 	printf("x = %f(%d) // south -> angle %f\n", wall_point.x, (int)(wall_point.x / TILE_SIZE), angle);
	// else
	// 	printf("x = %f(%d) // north -> angle %f\n", wall_point.x, (int)(wall_point.x / TILE_SIZE), angle);
	setup_x_coord(&texture, wall_point, game->horizontal_point);
	return (texture);
}
