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
		temp->texture = 'x';
		temp->distance = INF;
		temp->cx = 0;
		temp->cy = 0;
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
	{
		free(rays[i]);
	}
	free(rays);
}

void	draw_rays(t_game *game)
{
	float	d;
	float	c;
	float	prec;
	int		i;
	int		j;
	int		k;

	prec = game->window->width / RAYS;
	i = -1;
	while (++i < RAYS)
	{
		d = 400 / game->world->rays[i]->distance;
		c = 255 / game->world->rays[i]->distance;
		j = -d / 2 - 1;
		while (++j < d / 2)
		{
			k = -1;
			while (++k < prec)
			{
				mlx_pixel_put(game->window->mlx_ptr,
						game->window->win_ptr,
						i * prec + k,
						(int)(game->window->height / 2 + j),
						rgb(c, c, c));
			}
		}
	}
	rotate_ray_array(game->world->rays, 10);
}
