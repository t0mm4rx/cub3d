#include "cub3d.h"

int key_pressed(int key, void *game)
{
  if (key == 12 || key == 53)
		stop_game(game);
  if (key == 126)
    ((t_game*)game)->keys->k_up = 1;
  if (key == 125)
    ((t_game*)game)->keys->k_down = 1;
  if (key == 123)
    ((t_game*)game)->keys->k_left = 1;
  if (key == 124)
    ((t_game*)game)->keys->k_right = 1;
  return (0);
}

int key_released(int key, void *game)
{
  if (key == 126)
    ((t_game*)game)->keys->k_up = 0;
  if (key == 125)
    ((t_game*)game)->keys->k_down = 0;
  if (key == 123)
    ((t_game*)game)->keys->k_left = 0;
  if (key == 124)
    ((t_game*)game)->keys->k_right = 0;
  return (0);
}
