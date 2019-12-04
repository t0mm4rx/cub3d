#include "cub3d.h"

void	raycast(t_world *world)
{
	int	i;
	float	buffer[4] = {9999};
	float	min;

	i = -1;
	while (++i < RAYS)
	{
		min = INF;
		buffer[0] = raycast_left(world->rays[i], world);
		buffer[1] = raycast_right(world->rays[i], world);
		buffer[2] = raycast_top(world->rays[i], world);
		//buffer[3] = raycast_bottom(world->rays[i], world);
		//buffer[2] = INF;
		buffer[3] = INF;
		if (buffer[0] < min)
		{
			min = buffer[0];
			world->rays[i]->texture = 'o';
			world->rays[i]->distance = buffer[0];
		}
		if (buffer[1] < min)
		{
			min = buffer[1];
			world->rays[i]->texture = 'e';
			world->rays[i]->distance = buffer[1];
		}
		if (buffer[2] < min)
		{
			min = buffer[2];
			world->rays[i]->texture = 'n';
			world->rays[i]->distance = buffer[2];
		}
		if (buffer[3] < min)
		{
			min = buffer[3];
			world->rays[i]->texture = 's';
			world->rays[i]->distance = buffer[3];
		}
	}
}

float	raycast_left(t_ray *ray, t_world *world)
{
	float nx;
	float ny;

	if (ray->angle <= 270 && ray->angle >= 90)
		return (INF);
	ray->cx = world->px;
	ray->cy = world->py;
	while ((int)floor(ray->cx) < world->mx && (int)floor(ray->cy) < world->my
	&& ray->cx > 0 && ray->cy > 0 && !world->map[(int)floor(ray->cx)][(int)floor(ray->cy)])
	{
		nx = floor(ray->cx + 1) - ray->cx;
		nx = (!nx ? 1 : nx);
		ny = tan(deg_to_rad(ray->angle)) * nx;
		ray->cx += nx;
		ray->cy += ny;
	}
	return (dist(ray->cx, ray->cy, world->px, world->py));
}

float	raycast_right(t_ray *ray, t_world *world)
{
	float nx;
	float ny;

	if (ray->angle >= 270 || ray->angle <= 90)
		return (INF);
	ray->cx = world->px;
	ray->cy = world->py;
	while ((int)floor(ray->cx - 1) < world->mx && (int)floor(ray->cy) < world->my
	&& ray->cx - 1 > 0 && ray->cy > 0 && !world->map[(int)floor(ray->cx - 1)][(int)floor(ray->cy)])
	{
		nx = -(ray->cx - floor(ray->cx));
		nx = (!nx ? -1 : nx);
		ny = tan(deg_to_rad(ray->angle)) * nx;
		ray->cx += nx;
		ray->cy += ny;
	}
	return (dist(ray->cx, ray->cy, world->px, world->py));
}

float	raycast_top(t_ray *ray, t_world *world)
{
	float nx;
	float ny;
	if (ray->angle >= 180)
		return (INF);
	ray->cx = world->px;
	ray->cy = world->py;
	while ((int)floor(ray->cx) < world->mx && (int)floor(ray->cy) < world->my
	&& ray->cx > 0 && ray->cy > 0 && !world->map[(int)floor(ray->cx)][(int)floor(ray->cy)])
	{
		ny = floor(ray->cy + 1) - ray->cy;
		ny = (!ny ? -1 : ny);
		nx = tan(deg_to_rad(90 - ray->angle)) * ny;
		ray->cx += nx;
		ray->cy += ny;
	}
	return (dist(ray->cx, ray->cy, world->px, world->py));
}

float	raycast_bottom(t_ray *ray, t_world *world)
{
	float nx;
	float ny;

	if (ray->angle <= 180)
		return (INF);
	ray->cx = world->px;
	ray->cy = world->py;
	while ((int)floor(ray->cx) < world->mx && (int)floor(ray->cy - 1) < world->my
	&& ray->cx > 0 && ray->cy - 1 > 0 && !world->map[(int)floor(ray->cx)][(int)floor(ray->cy - 1)])
	{
		ny = -(ray->cy - floor(ray->cy));
		ny = (!ny ? 1 : ny);
		nx = tan(deg_to_rad(90 - ray->angle)) * ny;
		ray->cx += nx;
		ray->cy += ny;
	}
	return (dist(ray->cx, ray->cy, world->px, world->py));
}
