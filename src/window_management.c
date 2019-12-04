#include "cub3d.h"

int			loop_hook(void *param)
{
	if (((t_game *)param)->draw)
		((t_game *)param)->draw(param);
	return (1);
}

t_window	*create_window(unsigned int width, unsigned int height, const char *title, t_game *game)
{
	t_window	*res;
	int			config[3];

	if (!(res = ft_calloc(sizeof(t_window), 1)))
		return (NULL);
	config[0] = 32;
	config[1] = width * 4;
	config[2] = 0;
	res->width = width;
	res->height = height;
	res->title = title;
	res->mlx_ptr = mlx_init();
	res->win_ptr = mlx_new_window(res->mlx_ptr, width, height, (char *)title);
	res->surface = mlx_new_image(res->mlx_ptr, width, height);
	res->data = mlx_get_data_addr(res->surface,
			&config[0], &config[1], &config[2]);
	mlx_hook(res->win_ptr, 2, 1L << 0, &key_pressed, game);
	mlx_hook(res->win_ptr, 3, 1L << 1, &key_released, game);
	mlx_hook(res->win_ptr, 17, 1L << 17, &program_exited, game);
	mlx_loop_hook(res->mlx_ptr, &loop_hook, game);
	return (res);
}

t_keys	*create_keys(void)
{
	t_keys	*res;

	if (!(res = ft_calloc(sizeof(t_keys), 1)))
		return (NULL);
	res->k_up = 0;
	res->k_down = 0;
	res->k_left = 0;
	res->k_right = 0;
	return (res);
}
