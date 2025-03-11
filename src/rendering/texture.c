#include "cub3d.h"

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
	setup_x_coord(&texture, wall_point, game->horizontal_point);
	return (texture);
}
