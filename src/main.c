#include "cub3d.h"

int main(void)
{
	t_world *world = create_world();
	raycast(world);
	print_world(world);
	stop_game(world);
	return (0);
}
