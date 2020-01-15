#include "cub3d.h"

void    destroy_sprite(void *content)
{
  free(content);
}

t_list  *create_sprites_array(t_info *info)
{
  t_list    *res;
  t_sprite  *sprite;
  int       x;
  int       y;

  res = NULL;
  x = -1;
  while (++x < info->map_width)
  {
    y = -1;
    while (++y < info->map_height)
    {
      if (info->map[x][y] == 2)
      {
        sprite = ft_calloc(sizeof(t_sprite), 1);
        sprite->x = x;
        sprite->y = y;
        ft_lstadd_back(&res, ft_lstnew(sprite));
        sprite = NULL;
      }
    }
  }

  t_list *ptr = res;
  while (ptr)
  {

    ptr = ptr->next;
  }

  return (res);
}

void draw_sprites(t_game *game)
{
    t_list *ptr;
    t_sprite *sprite;

    float dir_x = cos(deg_to_rad(game->world->angle));
    float dir_y = sin(deg_to_rad(game->world->angle));

    ptr = game->world->sprites;
    while (ptr)
    {
      sprite = ptr->content;
      float sprite_x = sprite->x - game->world->px;
      float sprite_y = sprite->y - game->world->py;
      float inv_det = 1.0 / (game->world->plane_x * dir_y - dir_x * -game->world->plane_y);
      float transform_x = inv_det * ((dir_y * sprite_x) - (dir_x * sprite_y));
      float transform_y = inv_det * (game->world->plane_y * sprite_x + game->world->plane_x * sprite_y);
      int sprite_screen_x = (int)((game->window->width / 2) * (1 + transform_x / transform_y));
      int sprite_height = abs((int)(game->window->height / (transform_y)));
      int draw_start_y = -sprite_height / 2 + game->window->height / 2 + game->world->pz;
      int draw_end_y = sprite_height / 2 + game->window->height / 2 + game->world->pz;
      int sprite_width = abs((int)(game->window->height / (transform_y)));
      int draw_start_x = -sprite_width / 2 + sprite_screen_x;
      int draw_end_x = sprite_width / 2 + sprite_screen_x;
      //if(draw_end_x >= (int)game->window->width) draw_end_x = game->window->width - 1;
      //loop through every vertical stripe of the sprite on screen
      for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
      {
        if(transform_y > 0 && stripe > 0 && stripe < (int)game->window->width/* && transform_y < ZBuffer[stripe]*/)
        for(int y = draw_start_y; y < draw_end_y; y++) //for every pixel of the current stripe
        {
          unsigned char color[4] = {0};
          int texture_x = ((float)(stripe - draw_start_x) / (float)(draw_end_x - draw_start_x)) * game->world->texture_sprite->width;
          int texture_y = (float)(y - draw_start_y) / (float)(draw_end_y - draw_start_y) * game->world->texture_sprite->height;
          get_pixel_color(game->world->texture_sprite, texture_x, texture_y, color);
          if (color[3] != 255 || y < 0 || y >= (int)game->window->height
          || stripe < 0 || stripe >= (int)game->window->width)
            draw_pixel(game->window, stripe, y, color);
          //printf("%d %d %d %d\n", color[0], color[1], color[2], color[3]);
        }
      }
      ptr = ptr->next;
    }
}
