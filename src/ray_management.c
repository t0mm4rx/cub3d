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
	t_rect	rect;
	int			i;
	int			c;
	int			res;
	int			d;
	char		color[4];

	res = game->window->width / RAYS;
	i = -1;
	while (++i < RAYS)
	{
			c = (int)(255 / game->world->rays[i]->distance);
			d = (int)(500 / game->world->rays[i]->distance);
			rect.x = i * res;
			rect.y = (int)(game->window->height / 2 - d / 2);
			rect.width = res;
			rect.height = d;
			color[0] = c;
			color[1] = c;
			color[2] = c;
			color[3] = 0;
			draw_rect(game->window, rect, color);
	}
}
