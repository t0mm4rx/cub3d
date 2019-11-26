#include "cub3d.h"

int main(void)
{
	t_ray **rays = create_ray_array(0);
	rotate_ray_array(rays, 350.0);
	free_ray_array(rays);

	int **map = create_2d_array(10, 10);
	map[0][0] = 1;
	print_2d_array(map, 10, 10);
	free_2d_array(map, 10);
	return (0);
}
