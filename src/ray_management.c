#include "cub3d.h"

t_ray	**create_ray_array(float angle)
{
	int	i;
	float	a;
	t_ray	**res;
	t_ray	*temp;

	if (!(res = ft_calloc(sizeof(t_ray *), RAYS)))
		return (NULL);
	i = 0;
	while (i < RAYS)
	{
		a = (-FOV / 2) + (FOV / RAYS) * i;
		temp = ft_calloc(sizeof(t_ray), 1);
		temp->angle = mod(a + angle, 360.0);
		temp->texture = NULL;
		temp->distance = INF;
		res[i] = temp;
		i += 1;
	}
	return (res);
}

void	rotate_ray_array(t_ray **rays, float angle)
{
	int i;

	i = RAYS;
	while (i--)
	{
		rays[i]->angle += angle;
		rays[i]->angle = mod(rays[i]->angle, 360.0);
	}
}

void	free_ray_array(t_ray **rays)
{
	int i;

	i = RAYS;
	while (i--)
		free(rays[i]);
	free(rays);
}

void	draw_rays(t_game *game)
{
	int						i;
	int						res;
	int						d;
	int						x;
	int						y;
	int						a;
	unsigned char	color[4];

	res = ceil(game->window->width / RAYS);
	i = -1;
	while (++i < RAYS)
	{
			d = (int)(game->window->height / game->world->rays[i]->distance);
			x = i * res;
			while (x < i * res + res)
			{
				y = (int)(game->window->height / 2 - d / 2) + game->world->pz;
				a = 0;
				while (y < (int)(game->window->height / 2 - d / 2) + game->world->pz + d)
				{
					get_pixel_color(game->world->rays[i]->texture,
						game->world->rays[i]->wall_x * game->world->rays[i]->texture->width,
						(int)floor((float)(a) / (float)(d) * game->world->rays[i]->texture->height),
						color);
					draw_pixel(game->window, x, y, color);
					y++;
					a++;
				}
				x++;
			}
	}
}
