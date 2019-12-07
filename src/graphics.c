#include "cub3d.h"

void	draw_rect(t_window *window, t_rect rect, unsigned char color[4])
{
	int i;
	int j;

	i = -1;
	while (++i < rect.width)
	{
		j = -1;
		while (++j < rect.height)
			draw_pixel(window, rect.x + i, rect.y + j, color);
	}
}

void	clear_data(t_window *window)
{
	t_rect			rect;
	unsigned char	color[4];

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
	rect.x = 0;
	rect.y = 0;
	rect.width = window->width;
	rect.height = window->height;
	draw_rect(window, rect, color);
}

void	draw_pixel(t_window *window, unsigned int x, unsigned int y,
	unsigned char color[4])
{
	int index;
	int	i;

	if (x >= window->width || y >= window->height)
		return ;
	index = x * 4 + y * 4 * window->width;
	i = -1;
	while (++i < 4)
		window->data[index + i] = color[i];
}
