/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:47:45 by tmarx             #+#    #+#             */
/*   Updated: 2020/01/15 11:50:33 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bmp_header(t_game *game, int fd, int filesize)
{
	unsigned char	data[54] = {0};

	data[0] = (unsigned char)('B');
	data[1] = (unsigned char)('M');
	int_to_char(filesize, data + 2);
	data[10] = (unsigned char)(54);
	data[14] = (unsigned char)(40);
	int_to_char(game->window->width, data + 18);
	int_to_char(game->window->height, data + 22);
	data[26] = (unsigned char)(1);
	data[28] = (unsigned char)(24);
	write(fd, data, 54);
}

static void	bmp_pixels(t_game *game, int fd, int pad)
{
	unsigned char	zero[3] = {0, 0, 0};
	unsigned int	i;
	unsigned int	j;
	int				color;

	i = 0;
	while (i < game->window->height)
	{
		j = 0;
		while (j < game->window->width)
		{
			color = get_pixel(game->window, j, i);
			write(fd, &color, 3);
			write(fd, &zero, pad);
			j++;
		}
		i++;
	}
}

int			screenshot(t_game *game)
{
	int			fd;
	int			filesize;
	int			pad;

	pad = (4 - (game->window->width * 3) % 4) % 4;
	filesize = 54 + (3 * (game->window->width + pad) * game->window->height);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT |
					O_TRUNC | O_APPEND, 0666)) < 0)
		return (0);
	bmp_header(game, fd, filesize);
	bmp_pixels(game, fd, pad);
	close(fd);
	return (1);
}
