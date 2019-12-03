#include "cub3d.h"

void	draw(t_game *game)
{
	mlx_clear_window(game->window->mlx_ptr, game->window->win_ptr);
	clear_data(game->window);
	raycast(game->world);
	print_world(game->world);
	draw_rays(game);
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
