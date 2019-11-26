#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include "libft.h"

# define RAYS 100.0
# define FOV 45.0

typedef struct	s_ray
{
	float	angle;
	char	texture;
	float	distance;
	int	offset_o;
	int	offset_n;
	int	offset_e;
	int	offset_s;
	int	cx;
	int	cy;
}		t_ray;

typedef struct	s_world
{
	int	**map;
	float	px;
	float	py;
	char	*texture_o;
	char	*texture_e;
	char	*texture_s;
	char	*texture_n;
}		t_world;

t_ray		**create_ray_array(float angle);
void		rotate_ray_array(t_ray **rays, float angle);
void		free_ray_array(t_ray **rays);
void		stop_game(void);
int		**create_2d_array(int x, int y);
void		free_2d_array(int **array, int x);

/*
** Utils functions
*/
float		mod(float a, float b);

/*
** Debug functions
*/
void		print_ray_array(t_ray **rays);
void		print_2d_array(int **array, int x, int y);
#endif
