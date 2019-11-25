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
