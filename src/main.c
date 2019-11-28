#include "cub3d.h"

/*int main(void)
{
	t_world *world = create_world();
	raycast(world);
	print_world(world);
	stop_game(world);
	return (0);
}*/

/*int	key_hook(int keycode, void *param)
{
	(void)param;
	printf("Key pressed: %d\n", keycode);
	if (keycode == 12)
		mlx_destroy_window(((data_s*)param)->mlx_win);
	return (1);
}*/

int main(void)
{
	t_game	*game;

	game = create_game(800, 600, "Cub3D by tmarx");
	//mlx_key_hook(data.mlx_win, &key_hook, &data);
	//mlx_loop(win->mlx_ptr);
	stop_game(game);
	return (0);
}
