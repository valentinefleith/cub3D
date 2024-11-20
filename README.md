# cub3D
3D graphical representation of the inside of a maze from a first-person perspective using Ray-Casting.
This project is inspired by the world-famous Wolfenstein 3D game, which was the fisrt FPS ever (1992).

[The subject](https://cdn.intra.42.fr/pdf/pdf/134410/en.subject.pdf)

# External functions
- open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday
- All functions of the math library (-lm man man 3 math)
- All functions of the MinilibX
- Libft

# Constraints are :

- Must use the miniLibX.
- Management of the window = smooth, changing to another window, minimizing etc.
- Display different wall textures that vary depending on which side th wll is facing (North/South/East/West)
- Must be able to set the floor and ceiling colors to two different ones.
- When the program displays the image in a window and respects the following rules:
  - Left and right arrow keys = look left and right in the maze.
  - W. A. S, D keys = move the point of view through the maze.
  - ESC key or clicking on the red cross = close the window + quit program properly.
  - The use of images of the minilibX is strongly recommended.
- Program must take as first argument a scene description file with the .cub extension.
  - Map must be composed of only 6 possible characters : 0 = empty space / 1 = a wall / N,S,E or W = the player's start position and spawning orientation.
  - The map must be closed/surrounded by walls (if not = return error)
  - Except for the map content which always has to be the last, each type of element can be set in any order in the file.
  - Except for the map. each type of information from an element can be separated by one or more space(s).
  - The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to tou to handle. You must be able to parse any kind of map, as long as it respects th rules of the map.
  - Each element (expect the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as : *North texture : `NO ./path_to_the_north_texture` (identifier : NO, path to the north texture). *South texture : `SO ./path_to_the_south_texture` (identifier : SO, .....), *Floor color : `F 200,100,0` (identifier: F, R,G,B colors in range [0,255] : 0, 255, 255).
  - If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.
