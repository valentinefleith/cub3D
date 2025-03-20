
# cub3D
Project : 3D graphical representation of the inside of a maze from a first-person perspective using Ray-Casting.

* [Game Loop](#Game_Loop)
* [Handle movement of the player](#Handle_movement)
* [Raycasting](#Raycasting)
* [Rendering](#)
* [Features](#)

## Game Loop

Before launching the game we need to initialize our data. If any error occurs during the initialization, the program prints a message and quits properly.

First of all we need to declare a pointer `mlx` and initialize it to keep the connection with the `MLX Library`, we'll need it for most of the functions during the program.

After that we call the function `init_textures(&game)` to download the textures (xpm format) and store them in a tab. Every cell of the texture's tab contains a struct with all the data about the image, like its pointer but also its width, how many bits per pixel etc.

Finally we can create a new window and fill in its width and height (which are constant value for the screen).

Then the game loop can start.
```
int	game_loop(t_maze *game)
{
	if (render_one_frame(game, true) == MLX_ERROR)
		return (MLX_ERROR);
	mlx_hook(game->win, 17, 0, exit_program, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, &mouse_move, game);
	mlx_loop_hook(game->mlx, &update_player_pos, game);
	mlx_loop(game->mlx);
	return (SUCCESS);
}
```
Here we use functions that constantly wait for events (inputs or signals) and when they intercept one, redirect it to the appropriate function to handle the event.
This is the job of functions `mlx_hook()`, `mlx_loop_hook()` and `mlx_loop()`.

More concretely the game loop : 
- waits for a key to be pressed, and when this is the case modify to true the boolean variable associated with the key.
- waits for a key to be released, when this the case modify to false the boolean variable associated with the key released.
- waits for a movement of the mouse in certain areas of the screen, and then modify the rotation of player's view angle.
- another function constantly checks which key has been pressed (i.e which is currently assigned to true) to modify game values, like player position and orientation (view direction).
- the last function is the global and main loop of the game.
When the key `ESC` is pressed or when the window is closed the program should free the data on the heap and ends properly.

*Here is useful documentation to help understanding this part more deeply*

[mlx Tutorials](https://gontjarow.github.io/MiniLibX/)
[mlx Documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)

# Handle movement

We update the coordinates of the player in the maze with the function `update_player_pos()`, depending on inputs we call the function `move_player()` or `rotate_player()`.

- For example, in the case where the key pressed was the "W", the player wants to move forward. So in function `move_player()` to update player's position we need to calculate cos and sin of the player's current angle of view. Then we multiply the angle with the player's speed (constant value) and add it to the old coordinates.
```
new_pos.x = (x_angle * PLAYER_SPEED) + player_pos.x;
new_pos.y = (y_angle * PLAYER_SPEED) + player_pos.y;
```
After that we need to check that the new position is not in a cell of the map where there is wall, to establish a ***collision***, if that's the case we don't update the position. To ensure that the collision is respected, we need to check every corner and edge of the cell.

- For the rotation we simply add the value of the rotation speed (still constant value) to the current looking angle.

Everytime an input is intercepted and handled correctly, the program perform raycasting again and update the image on the screen.

# Raycasting

To ***render one frame*** the procedure is as follows :
- Before creating a new image and puting it on the screen, if an image is already on the screen we must destroy it with the function `mlx_destroy_image(game->mlx, game->img.img)`
- We create a new image using mlx functions. For now the image is empty.
- During the raycasting process, each time a wall slice is detected, we print the pixels corresponding to the wall on our empty image.
- Once raycasting has completed the entire image, we can display the image on the screen by using the function `mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0)`

*We will describe the logic and procedure of raycasting, without going into too much detail as there is already a vast amount of documentation on the subject.*
This is the racasting loop.
```
void	raycasting(t_maze *maze)
{
	t_vector	wall_point;
	double		current_angle;
	double		distance;
	double		wall_height;
	int			x;

	current_angle = maze->player.looking_angle - (FOV_RADIANS / 2.0);
	x = 0;
	while (x < WIDTH)
	{
		current_angle = normalize_angle(current_angle);
		wall_point = find_wall_point(maze, current_angle);
		distance = get_wall_distance(maze->player.pos, wall_point, normalize_angle(maze->player.looking_angle), current_angle);
		wall_height = (TILE_SIZE / distance) * maze->plane_distance; // reminder plane_distance = (WIDTH / 2) / tan(FOV_RADIANS / 2)
		draw_wall(maze, setup_texture(maze, wall_point, current_angle), wall_height, x);
		current_angle += (FOV_RADIANS / (double)WIDTH);
		x++;
	}
}
```

We want to produce a 3D immersive first-person view and we are given a 2D map showing the *x*,*y* coordinates of each object (mostly walls here), coordinates of the player and its angle of view.

To do so, from the player's position we'll cast rays covering its entire ***field of vision***. These rays will allow us to measure the ***distance*** between the walls and the player. This information will help us to determine the height of the wall we're facing. A wall is at a great distance from me, if I draw this wall it will appear very small, but if I'm very close to it, its height will seem much greater. Progressively this will create perspective.

We cast as many rays as there are pixel columns in our screen.

*Here is useful documentation to help understanding this part more deeply*

[Lode's Tutorial - using vector and camera](https://lodev.org/cgtutor/raycasting.html)
[Raycasting tutorial with different level](https://github.com/vinibiavatti1/RayCastingTutorial/wiki)
[Story and main logic](https://xitog.github.io/dgx/passetemps/tech_raycasting_fr.html)
[Description of the steps with schema](https://guy-grave.developpez.com/tutoriels/jeux/doom-wolfenstein-raycasting/)
