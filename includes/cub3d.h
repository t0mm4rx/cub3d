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

t_ray		**create_ray_array(float angle);
void		rotate_ray_array(t_ray **rays, float angle);
void		free_ray_array(t_ray **rays);
void		stop_game(void);

/*
** Utils functions
*/
float		mod(float a, float b);
//float		fabs(float a);

/*
** Debug functions
*/
void		print_ray_array(t_ray **rays);
#endif
