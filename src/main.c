#include "cub3d.h"

void	update(t_game *game)
{
	if (game->keys->k_right)
		rotate_ray_array(game->world->rays, ROTATE_SPEED);
	if (game->keys->k_left)
		rotate_ray_array(game->world->rays, -ROTATE_SPEED);
	if (game->keys->k_up)
		game->world->px += PLAYER_SPEED;
	if (game->keys->k_down)
		game->world->px -= PLAYER_SPEED;
}

void	draw(t_game *game)
{
	update(game);
	mlx_clear_window(game->window->mlx_ptr, game->window->win_ptr);
	clear_data(game->window);
	raycast(game->world);
	draw_rays(game);
	print_world(game->world);
	mlx_put_image_to_window(game->window->mlx_ptr, game->window->win_ptr,
			game->window->surface, 0, 0);
}

int		main(void)
{
	t_game	*game;

	game = create_game(1000, 800, "Cub3D by tmarx");
	//print_world(game->world);
	game->draw = &draw;
	start_game(game);
	stop_game(game);
	return (0);
}
