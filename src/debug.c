/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:51:01 by tmarx             #+#    #+#             */
/*   Updated: 2020/01/15 11:52:13 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_ray_array(t_ray **rays)
{
	int i;

	i = -1;
	while (++i < RAYS)
	{
		printf("Ray (Angle: %f, Distance: %f)\n", rays[i]->angle,
				rays[i]->distance);
	}
}

void	print_2d_array(int **array, int x, int y)
{
	int i;
	int j;

	j = -1;
	while (++j < y)
	{
		i = -1;
		while (++i < x)
			printf(" %d ", array[i][j]);
		printf("\n");
	}
}

void	fill_map_borders(int **array, int x, int y)
{
	int i;

	i = -1;
	while (++i < x)
	{
		array[i][0] = 1;
		array[i][y - 1] = 1;
	}
	i = -1;
	while (++i < y)
	{
		array[0][i] = 1;
		array[x - 1][i] = 1;
	}
	array[8][8] = 1;
	array[7][8] = 1;
	array[7][7] = 1;
	array[3][3] = 1;
}

void	print_world(t_world *world)
{
	print_ray_array(world->rays);
	printf("\n");
	print_2d_array(world->map, world->mx, world->my);
	printf("\nAngle: %f\n", world->angle);
	printf("Position: (%10f, %10f)\n", world->px, world->py);
}

void	print_info(t_info *info)
{
	printf("Width: %d\nHeight: %d\n", info->width, info->height);
	printf("PX: %d\nPY: %d\nAngle: %c\n", info->px, info->py,
			info->orientation);
	printf("Ceil: %d, %d, %d\n", info->ceil[0], info->ceil[1],
			info->ceil[2]);
	printf("Floor: %d, %d, %d\n", info->floor[0], info->floor[1],
			info->floor[2]);
}
