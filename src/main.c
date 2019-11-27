#include "cub3d.h"

/*int main(void)
{
	t_world *world = create_world();
	raycast(world);
	print_world(world);
	stop_game(world);
	return (0);
}*/

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

int	key_hook(int keycode, void *param)
{
	(void)param;
	printf("Key pressed: %d\n", keycode);
	return (1);
}

int	loop_hook(void *param)
{
	(void)param;
	printf("loop\n");
	return (0);
}

int main(void)
{
	data_t        data;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	mlx_key_hook(data.mlx_win, &key_hook, NULL);
	mlx_loop_hook(data.mlx_win, &loop_hook, NULL);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
