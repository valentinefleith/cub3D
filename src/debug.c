#include "cub3d.h"

void	debug_textures_path(char **tab)
{
	int i = 0;

	if (!tab)
	{
		printf("ERROR > The array with the path of textures is NULL\n");
		return ;
	}
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
}

void debug_colors(int floor[3], int ceilling[3])
{
	int i = 0;
	printf("FLOOR RGB \n");
	while (i < 3)
	{
		printf("cell %i : %d\n", i, floor[i]);
		i++;
	}
	i = 0;
	printf("CEILLING RGB \n");
	while (i < 3)
	{
		printf("cell %i : %d\n", i, ceilling[i]);
		i++;
	}
}