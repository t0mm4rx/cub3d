#include "cub3d.h"

t_game	*create_game(t_info *info, const char *title)
{
	t_game *res;

	if (!(res = ft_calloc(sizeof(t_game), 1)))
		return (NULL);
	res->world = create_world(info);
	res->keys = create_keys();
	res->draw = NULL;
	res->window = create_window(info->width, info->height, title, res);
	return (res);
}

void	start_game(t_game *game)
{
	mlx_loop(game->window->mlx_ptr);
}

t_world	*create_world(t_info *info)
{
	t_world	*res;

	if (!(res = ft_calloc(sizeof(t_world), 1)))
		return (NULL);
	res->angle = info->angle;
	if (!(res->rays = create_ray_array(res->angle)))
		return (NULL);
	res->map = info->map;
	res->mx = info->map_width;
	res->my = info->map_height;
	res->px = info->px;
	res->py = info->py;
	res->pz = 0;
	res->jump_time = -1;
	return (res);
}

void	stop_game(t_game *game)
{
	printf("Exiting the game, cleaning up...");
	free_2d_array(game->world->map, game->world->mx);
	free_ray_array(game->world->rays);
	free(game->world);
	mlx_destroy_window(game->window->mlx_ptr, game->window->win_ptr);
	mlx_destroy_image(game->window->mlx_ptr, game->window->surface);
	free(game->window);
	free(game->keys);
	free(game);
	exit(EXIT_SUCCESS);
}
