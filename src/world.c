#include "cub3d.h"

t_world	*create_world(void)
{
	t_world	*res;

	if (!(res = ft_calloc(sizeof(t_world), 1)))
		return (NULL);
	if (!(res->rays = create_ray_array(0)))
		return (NULL);
	res->map = create_2d_array(10, 10);
	res->mx = 10;
	res->my = 10;
	res->px = 5;
	res->py = 5;
	fill_map_borders(res->map, res->mx, res->my);
	return (res);
}

void	stop_game(t_world *world)
{
	free_2d_array(world->map, world->mx);
	free_ray_array(world->rays);
	free(world);
}
