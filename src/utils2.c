#include "cub3d.h"

void update_jump(t_game *game)
{
  if (game->world->jump_time >= 0)
  {
    game->world->jump_time++;
    game->world->pz = (-1 * ((game->world->jump_time / 4 - 3) * (game->world->jump_time / 4 - 3)) + 9) * JUMP_HEIGHT;
  }
  if (game->world->jump_time >= 24)
  {
    game->world->jump_time = -1;
    game->world->pz = 0;
  }
}
