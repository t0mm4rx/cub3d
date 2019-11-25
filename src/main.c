#include "cub3d.h"

int main(void)
{
	t_ray **rays = create_ray_array(0);
	print_ray_array(rays);
	rotate_ray_array(rays, 350.0);
	print_ray_array(rays);
	free_ray_array(rays);
	return (0);
}
