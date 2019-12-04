#include "cub3d.h"

void rotate(t_game *game, int direction)
{
  rotate_ray_array(game->world->rays, direction * ROTATE_SPEED);
  game->world->angle += direction * ROTATE_SPEED;
  game->world->angle = mod(game->world->angle, 360);
}

void go(t_game *game, int direction)
{
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
}
