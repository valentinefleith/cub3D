#include "cub3d.h"

int	init_keys(t_maze *game)
{
	int	i;

	if (!game)
		return (KO);
	i = 0;
	while (i < 6)
	{
		game->player.keys_pressed[i] = false;
		i++;
	}
	return (SUCCESS);
}

static int	update_position(t_maze *game, double x_angle, double y_angle, t_vector player_pos)
{
	t_point		grid;
	t_vector	new_pos;

	if (!game)
		return (KO);
	new_pos.x = round((x_angle * PLAYER_SPEED) + player_pos.x);
	new_pos.y = round((y_angle * PLAYER_SPEED) + player_pos.y);
	grid.x = (new_pos.x / TILE_SIZE);
	grid.y = (new_pos.y / TILE_SIZE);
	// printf("ALOOOOO\n");
	if (grid.y < 0 || grid.x < 0 
		|| grid.y >= game->map->dimensions.height 
		|| grid.x >= game->map->dimensions.width)
		return (KO);
	if (game->map->maze[grid.y] && game->map->maze[grid.y][grid.x] != '1')
		game->player.pos = new_pos;
	else
		return (KO);
	render_one_frame(game, false);
	return (SUCCESS);
}

static int move_player(t_maze *game, double angle, int key_pressed)
{
	double	sine;
	double	cosine;

	sine = sin(angle);
	cosine = cos(angle);
	// if (key_pressed == XK_d)
	// 	return (update_position(game, -sine, cosine, game->player.pos));
	// else if (key_pressed == XK_a)
	// 	return (update_position(game, sine, -cosine, game->player.pos));
	// else if (key_pressed == XK_w)
	// 	return (update_position(game, cosine, sine, game->player.pos));
	// else if (key_pressed == XK_s)
	// 	return (update_position(game, -cosine, -sine, game->player.pos));
	if (key_pressed == right)
		return (update_position(game, -sine, cosine, game->player.pos));
	else if (key_pressed == left)
		return (update_position(game, sine, -cosine, game->player.pos));
	else if (key_pressed == up)
		return (update_position(game, cosine, sine, game->player.pos));
	else if (key_pressed == down)
		return (update_position(game, -cosine, -sine, game->player.pos));
	return (KO);
}

static int rotate_player(t_maze *game, int key_pressed)
{
	if (key_pressed == left_rotation)
	{
		game->player.looking_angle += ROTATION_SPEED;
		if (game->player.looking_angle > 2.0 * M_PI)
			game->player.looking_angle -= 2.0 * M_PI;
		// game->player.keys_pressed[left_rotation] = false;
		return (render_one_frame(game, false));
	}
	else if (key_pressed == right_rotation)
	{
		game->player.looking_angle -= ROTATION_SPEED;
		if (game->player.looking_angle < 0)
			game->player.looking_angle += 2.0 * M_PI;
		// game->player.keys_pressed[right_rotation] = false;
		return (render_one_frame(game, false));
	}
	return (KO);
}

// static void debug_player(t_maze *game)
// {
// 	if (game->player.key_pressed == none)
// 		printf("key is NONE\n");
// 	if (game->player.key_pressed == up)
// 		printf("key is UP\n");
// 	if (game->player.key_pressed == down)
// 		printf("key is DOWN\n");
// 	if (game->player.key_pressed == left)
// 		printf("key is LEFT\n");
// 	if (game->player.key_pressed == right)
// 		printf("key is RIGHT\n");
// 	if (game->player.key_pressed == left_rotation)
// 		printf("key is LEFT_ROTATION\n");
// 	if (game->player.key_pressed == right_rotation)
// 		printf("key is RIGHT_ROTATION\n");
// }

int	update_player_pos(t_maze *game)
{
	if (game->player.keys_pressed[0])
		move_player(game, game->player.looking_angle, 0);
	if (game->player.keys_pressed[1])
		move_player(game, game->player.looking_angle, 1);
	if (game->player.keys_pressed[2])
		move_player(game, game->player.looking_angle, 2);
	if (game->player.keys_pressed[3])
		move_player(game, game->player.looking_angle, 3);
	if (game->player.keys_pressed[4])
		rotate_player(game, 4);
	if (game->player.keys_pressed[5])
		rotate_player(game, 5);
	return (SUCCESS);
}

// int key_press(int keycode, t_maze *maze)
// {
// 	if (keycode == XK_s || keycode == XK_w || keycode == XK_a || keycode == XK_d)
// 		move_player(maze, maze->player.looking_angle, keycode);
// 		// return (move_player(maze, maze->player.looking_angle, keycode));
// 	if (keycode == XK_Right || keycode == XK_Left)
// 		rotate_player(maze, keycode);
// 		// return (rotate_player(maze, keycode));
// 	render_one_frame(maze);
// 	return 0;
// }