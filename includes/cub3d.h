#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define PLAYER_SPEED 0.1
# define ROTATE_SPEED 3.0
# define RAYS 200.0
# define FOV 45.0
# ifndef INF
#  define INF 100000000.0
# endif

typedef struct	s_rect {
	int x;
	int y;
	int width;
	int height;
}				t_rect;

typedef struct	s_keys {
	int k_up;
	int k_down;
	int k_left;
	int k_right;
	int k_a;
	int k_s;
	int k_d;
	int k_w;
}				t_keys;

typedef struct	s_window {
	void			*win_ptr;
	void			*mlx_ptr;
	void			*surface;
	char			*data;
	unsigned int	width;
	unsigned int	height;
	const char		*title;
}				t_window;

typedef struct	s_ray
{
	float	angle;
	char	texture;
	float	distance;
	int		offset_o;
	int		offset_n;
	int		offset_e;
	int		offset_s;
	float	cx;
	float	cy;
}				t_ray;

typedef struct	s_world
{
	float	angle;
	int				**map;
	t_ray			**rays;
	int				mx;
	int				my;
	float			px;
	float			py;
	char			*texture_o;
	char			*texture_e;
	char			*texture_s;
	char			*texture_n;
	unsigned char	color_ceil[4];
	unsigned char	color_ground[4];
}		t_world;

typedef struct	s_game
{
	t_window	*window;
	t_world		*world;
	t_keys		*keys;
	void		(*draw)(struct s_game *);
}				t_game;

/*
** Window management functions
*/
t_window	*create_window(unsigned int width, unsigned int height, const char *title, t_game *game);
void		close_window(t_window *window);
void		draw_rect(t_window *window, t_rect rect, unsigned char color[4]);
void		draw_pixel(t_window *window, unsigned int x, unsigned int y,
									unsigned char color[4]);
void		clear_data(t_window *window);
int			key_pressed(int key, void *param);
int			key_released(int key, void *param);
int 		program_exited(void *game);

/*
** Game functions
*/
t_game		*create_game(unsigned int width, unsigned int height, const char *title);
void		start_game(t_game *game);
t_ray		**create_ray_array(float angle);
t_keys	*create_keys(void);
void		rotate_ray_array(t_ray **rays, float angle);
void		free_ray_array(t_ray **rays);
void		raycast(t_world *world);
float		raycast_left(t_ray *ray, t_world *world);
float		raycast_right(t_ray *ray, t_world *world);
float		raycast_top(t_ray *ray, t_world *world);
float		raycast_bottom(t_ray *ray, t_world *world);
void		draw_rays(t_game *game);
void		stop_game(t_game *game);
int			**create_2d_array(int x, int y);
void		free_2d_array(int **array, int x);
t_world		*create_world(void);
void		draw(t_game *game);
void		rotate(t_game *game, int direction);
void		go(t_game *game, int direction);
void		draw_ceil_ground(t_game *game);

/*
** Utils functions
*/
float		mod(float a, float b);
float		deg_to_rad(float a);
float		dist(float a, float b, float x, float y);
void		set_color(unsigned char dest[4], unsigned char r, unsigned char g, unsigned char b);
int			min(int a, int b);
int			max(int a, int b);
float		minf(float a, float b);
float		maxf(float a, float b);

/*
** Debug functions
*/
void		print_ray_array(t_ray **rays);
void		print_2d_array(int **array, int x, int y);
void		fill_map_borders(int **array, int x, int y);
void		print_world(t_world *world);
#endif
