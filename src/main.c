#include "cub3d.h"

void	update(t_game *game)
{
	if (game->keys->k_right)
		rotate(game, 1);
	if (game->keys->k_left)
		rotate(game, -1);
	if (game->keys->k_up || game->keys->k_w)
		go(game, 0);
	if (game->keys->k_down || game->keys->k_s)
		go(game, 2);
	if (game->keys->k_a)
		go(game, 1);
	if (game->keys->k_d)
		go(game, 3);
	update_jump(game);
}

void	draw(t_game *game)
{
	update(game);
	mlx_clear_window(game->window->mlx_ptr, game->window->win_ptr);
	clear_data(game->window);
	//print_world(game->world);
	raycast(game->world);
	draw_ceil_ground(game);
	draw_rays(game);
	draw_hud(game);
	mlx_put_image_to_window(game->window->mlx_ptr, game->window->win_ptr,
			game->window->surface, 0, 0);
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		parsing_error(NULL);
	t_game *game;
	t_info *info = parse(argv[1]);
	game = create_game(info, "Cub3D by tmarx");
	destroy_info(info);
	set_color(game->world->color_ceil, 150, 80, 40);
	set_color(game->world->color_ground, 20, 50, 120);
	game->draw = &draw;

	char *result[4];
	get_pixel_color(game->world->texture_e, 0, 0, result);
	printf("-- %d %d %d %d --\n", result[0], result[1], result[2], result[3]);

	start_game(game);
	stop_game(game);
	return (0);
}
