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
    float plane_x = 0.0, plane_y = 0.66;


    t_list *ptr;
    t_sprite *sprite;

    float dir_x = cos(deg_to_rad(game->world->angle));
    float dir_y = sin(deg_to_rad(game->world->angle));

    ptr = game->world->sprites;
    //after sorting the sprites, do the projection and draw them
    while (ptr)
    {
      sprite = ptr->content;
      //translate sprite position to relative to camera
      float sprite_x = sprite->x - game->world->px;
      float sprite_y = sprite->y - game->world->px;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      float inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y); //required for correct matrix multiplication
      float transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
      float transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D

      int sprite_screen_x = (int)((game->window->width / 2) * (1 + transform_x / transform_y));

      //calculate height of the sprite on screen
      //int sprite_height = abs((int)(game->window->height / (transform_y))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int draw_start_y = -game->world->texture_sprite->height / 2 + game->window->height / 2;
      if(draw_start_y < 0) draw_start_y = 0;
      int draw_end_y = game->world->texture_sprite->height / 2 + game->window->height / 2;
      if(draw_end_y >= game->world->texture_sprite->height) draw_end_y = game->world->texture_sprite->height - 1;

      //calculate width of the sprite
      int sprite_width = abs((int) (game->window->height / (transform_y)));
      int draw_start_x = -game->world->texture_sprite->width / 2 + sprite_screen_x;
      if(draw_start_x < 0) draw_start_x = 0;
      int draw_end_x = sprite_width / 2 + sprite_screen_x;
      if(draw_end_x >= (int)game->window->width) draw_end_x = game->window->width - 1;
      //loop through every vertical stripe of the sprite on screen
      for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
      {
        //int tex_x = (int)(256 * (stripe - (-game->world->texture_sprite->width / 2 + sprite_screen_x)) * 64 / game->world->texture_sprite->width) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transform_y > 0 && stripe > 0 && stripe < (int)game->window->width/* && transform_y < ZBuffer[stripe]*/)
        for(int y = draw_start_y; y > draw_end_y; y--) //for every pixel of the current stripe
        {
          //int d = (y) * 256 - game->window->height * 128 + game->world->texture_sprite->height * 128; //256 and 128 factors to avoid floats
          //int texY = ((d * 64) / game->world->texture_sprite->height) / 256;
          //Uint32 color = sprite->texture->data->texture[game->world->texture_sprite->width * texY + texX]; //get current color from the texture
          unsigned char test[4] = {255,255,0, 0};
          //if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
          draw_pixel(game->window, stripe, y, test); //paint pixel if it isn't black, black is the invisible color
        }
      }
      ptr = ptr->next;
    }
}
