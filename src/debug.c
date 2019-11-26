#include "cub3d.h"

void	print_ray_array(t_ray **rays)
{
	int i;

	i = -1;
	while (++i < RAYS)
	{
		printf("Ray (Angle: %f, Distance: %f, Texture: %c)\n", rays[i]->angle, rays[i]->distance, rays[i]->texture);
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

void	fill_map_borders(int **array, int x, int y)
{
	int i;

	i = -1;
	while (++i < x)
	{
		array[i][0] = 1;
		array[i][y - 1] = 1;
	}
	i = -1;
	while (++i < y)
	{
		array[0][i] = 1;
		array[x - 1][i] = 1;
	}
}

void	print_world(t_world *world)
{
	print_ray_array(world->rays);
	printf("\n");
	print_2d_array(world->map, world->mx, world->my);
}
