#include "cub3d.h"

t_game	*create_game(unsigned int width, unsigned int height, const char *title)
{
	t_game *res;

	if (!(res = ft_calloc(sizeof(t_game), 1)))
		return (NULL);
	res->world = create_world();
	res->draw = NULL;
	res->window = create_window(width, height, title, res);
	return (res);
}

void	start_game(t_game *game)
{
	mlx_loop(game->window->mlx_ptr);
}

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

void	stop_game(t_game *game)
{
	printf("Exiting the game, cleaning up...");
	free_2d_array(game->world->map, game->world->mx);
	free_ray_array(game->world->rays);
	free(game->world);
	mlx_destroy_window(game->window->mlx_ptr, game->window->win_ptr);
	free(game->window);
	free(game);
	exit(EXIT_SUCCESS);
}
