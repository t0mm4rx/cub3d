/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:47:08 by tmarx             #+#    #+#             */
/*   Updated: 2020/01/15 11:47:27 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		**create_2d_array(int x, int y)
{
	int **res;

	if (!(res = ft_calloc(sizeof(int *), x)))
		return (NULL);
	while (x--)
		res[x] = ft_calloc(sizeof(int), y);
	return (res);
}

void	free_2d_array(int **array, int x)
{
	while (x--)
		free(array[x]);
	free(array);
}
