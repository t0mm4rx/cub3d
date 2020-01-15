#include "cub3d.h"

t_game	*create_game(t_info *info, const char *title)
{
	t_game *res;

	if (!(res = ft_calloc(sizeof(t_game), 1)))
		return (NULL);
	res->world = create_world(info);
	res->keys = create_keys();
	res->draw = NULL;
	res->window = create_window(info, title, res);
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
	res->angle = 0;
	if (info->orientation == 'N')
		res->angle = -90;
	if (info->orientation == 'W')
		res->angle = 180;
	if (info->orientation == 'S')
		res->angle = 90;
	if (!(res->rays = create_ray_array(res->angle)))
		return (NULL);
	res->map = info->map;
	res->mx = info->map_width;
	res->my = info->map_height;
	res->px = info->px;
	res->py = info->py;
	res->pz = 0;
	res->plane_x = 0.0;
	res->plane_y = 0.40;
	res->jump_time = -1;
	res->texture_e = info->texture_e;
	res->texture_s = info->texture_s;
	res->texture_o = info->texture_w;
	res->texture_n = info->texture_n;
	res->texture_sprite = info->texture_sprite;
	res->sprites = create_sprites_array(info);
	return (res);
}

void	stop_game(t_game *game)
{
	printf("Exiting the game, cleaning up...");
	if (game->screenshot)
		screenshot(game);
	destroy_texture(game->window->mlx_ptr, game->world->texture_n);
	destroy_texture(game->window->mlx_ptr, game->world->texture_s);
	destroy_texture(game->window->mlx_ptr, game->world->texture_e);
	destroy_texture(game->window->mlx_ptr, game->world->texture_o);
	destroy_texture(game->window->mlx_ptr, game->world->texture_sprite);
	mlx_destroy_window(game->window->mlx_ptr, game->window->win_ptr);
	mlx_destroy_image(game->window->mlx_ptr, game->window->surface);
	free_2d_array(game->world->map, game->world->mx);
	free_ray_array(game->world->rays);
	ft_lstclear(&(game->world->sprites), &destroy_sprite);
	free(game->world);
	free(game->window);
	free(game->keys);
	free(game);
	exit(EXIT_SUCCESS);
}
