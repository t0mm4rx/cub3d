#include "cub3d.h"

void	print_ray_array(t_ray **rays)
{
	int i;

	i = -1;
	while (++i < RAYS)
	{
		printf("Ray (Angle: %f, Texture: %c)\n", rays[i]->angle, rays[i]->texture);
	}
}

void	print_2d_array(int **array, int x, int y)
{
	int i;
	int j;

	j = -1;
	while (++j < y)
	{
		i = -1;
		while (++i < x)
			printf(" %d ", array[i][j]);
		printf("\n");
	}
}
