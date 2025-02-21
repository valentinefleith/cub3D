#include "cub3d.h"
#include "raycasting.h"

double	normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return (angle);
}

void	draw_fov(t_maze *maze)
{
	t_position	center_pos;

	center_pos.y = TILE_SIZE / 2;
	for (int i = 0; i < maze->map->dimensions.height; i++)
	{
		center_pos.x = TILE_SIZE / 2;
		for (int j = 0; j < maze->map->dimensions.width; j++)
		{
			if (maze->map->maze[i][j] == '1')
				draw_rectangle(maze, center_pos, TILE_SIZE,
					TILE_SIZE, WHITE);
			else
				draw_rectangle(maze, center_pos, TILE_SIZE,
					TILE_SIZE, GREY);
			center_pos.x = center_pos.x + TILE_SIZE;
		}
		center_pos.y = center_pos.y + TILE_SIZE;
	}
	draw_grid(maze);
	draw_rectangle(maze, maze->player.pos, PLAYER_WIDTH_PX, PLAYER_WIDTH_PX,
		GREEN);
	draw_line_from_angle(maze, maze->player.pos, maze->player.looking_angle,
		70, RED);
	// raycasting(maze);
}
