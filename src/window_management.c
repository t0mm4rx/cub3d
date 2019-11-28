#include "cub3d.h"

int			key_hook(int keycode, void *param)
{
	printf("Key pressed %d\n", keycode);
	if (keycode == 12 || keycode == 53)
		stop_game(param);
	return (1);
}

t_window	*create_window(unsigned int width, unsigned int height, const char *title, t_game *game)
{
	t_window	*res;

	if (!(res = ft_calloc(sizeof(t_window), 1)))
		return (NULL);
	res->width = width;
	res->height = height;
	res->title = title;
	res->mlx_ptr = mlx_init();
	res->win_ptr = mlx_new_window(res->mlx_ptr, width, height, (char *)title);
	mlx_key_hook(res->win_ptr, &key_hook, game);
	return (res);
}
