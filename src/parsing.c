/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarx <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:04:25 by tmarx             #+#    #+#             */
/*   Updated: 2020/01/15 12:06:39 by tmarx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	*parse(char *file)
{
	t_info	*res;
	int		fd;
	int		status;
	char	*line;

	fd = open(file, O_RDONLY);
	res = ft_calloc(sizeof(t_info), 1);
	if (fd < 0)
		parsing_error(res);
	res->tmp_mlx_ptr = mlx_init();
	while ((status = get_next_line(fd, &line)) > 0)
	{
		handle_line(line, res);
		free(line);
	}
	handle_line(line, res);
	free(line);
	if (!check_parsing(res))
		parsing_error(res);
	create_map(res);
	return (res);
}

void	handle_line(char *line, t_info *info)
{
	if (*line == '\0')
		return ;
	if (!ft_isdigit(*line) && info->map_started)
		parsing_error(info);
	if (ft_isdigit(*line))
	{
		info->map_started = 1;
		handle_line_map(line, info);
	}
	else
		handle_line_info(line, info);
}

int		check_parsing(t_info *info)
{
	if (info->width <= 0 || info->height <= 0)
		return (0);
	if (!info->texture_n->ptr || !info->texture_s->ptr || !info->texture_w->ptr
		|| !info->texture_e->ptr || !info->texture_sprite->ptr)
		return (0);
	if (!check_map(info))
		return (0);
	return (1);
}

void	parsing_error(t_info *info)
{
	destroy_info(info);
	write(1, "Error\n", 6);
	exit(0);
}
