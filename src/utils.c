#include "cub3d.h"

void	set_color(unsigned char color[4], unsigned char r, unsigned char g, unsigned char b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = 0;
}

void	rotate(t_game *game, int direction)
{
  rotate_ray_array(game->world->rays, direction * ROTATE_SPEED);
  game->world->angle += direction * ROTATE_SPEED;
  game->world->angle = mod(game->world->angle, 360);
}

void	go(t_game *game, int direction)
{
	float	pos_x;
	float	pos_y;

	pos_x = game->world->px;
	pos_y = game->world->py;
	if (direction == 0)
	{
		game->world->px += cos(deg_to_rad(game->world->angle)) * PLAYER_SPEED;
		game->world->py += sin(deg_to_rad(game->world->angle)) * PLAYER_SPEED;
	}
  if (direction == 1)
  {
    game->world->px += cos(deg_to_rad(game->world->angle - 90)) * PLAYER_SPEED;
    game->world->py += sin(deg_to_rad(game->world->angle - 90)) * PLAYER_SPEED;
  }
  if (direction == 2)
  {
    game->world->px -= cos(deg_to_rad(game->world->angle)) * PLAYER_SPEED;
    game->world->py -= sin(deg_to_rad(game->world->angle)) * PLAYER_SPEED;
  }
  if (direction == 3)
  {
    game->world->px += cos(deg_to_rad(game->world->angle + 90)) * PLAYER_SPEED;
    game->world->py += sin(deg_to_rad(game->world->angle + 90)) * PLAYER_SPEED;
  }
	if (game->world->map[(int)floor(game->world->px)][(int)floor(game->world->py)] == 1)
	{
		game->world->px = pos_x;
		game->world->py = pos_y;
	}
}

void	draw_ceil_ground(t_game *game)
{
	t_rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.height = game->window->height / 2 + game->world->pz;
	rect.width = game->window->width;
	draw_rect(game->window, rect, game->world->color_ceil);
	rect.y = rect.height;
	draw_rect(game->window, rect, game->world->color_ground);
}
void	jump(t_game *game)
{
	if (game->world->jump_time == -1)
		game->world->jump_time = 0;
}
