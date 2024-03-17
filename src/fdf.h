/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:04:50 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/17 17:38:22 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx_int.h>
# include "get_next_line.h"
# include "keysymdef.h"

# define WHITE 			0x00FFFFFF
# define RED 			0x00FF0000
# define BLUE 			0x000000FF
# define GREEN 			0x0000FF00
# define PURPLE 		0x00FF00FF
# define BLACK			0x00000000
# define DEFAULT_COLOR 	WHITE

# define WIDTH			1280
# define HEIGHT			720

# define CENTER_X 		640
# define CENTER_Y 		360
# define OFFSET_X		0
# define OFFSET_Y		0
# define SCALE 			5
# define DEPTH_SCALE	0.5

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bit_depth;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}	t_color;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;


typedef struct s_mat3
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
}	t_mat3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_mat4
{
	t_vec4	a;
	t_vec4	b;
	t_vec4	c;
	t_vec4	d;
}	t_mat4;

typedef struct s_point
{
	t_vec3			pos;
	unsigned int	col;
}	t_pt;

typedef struct s_map
{
	int		hei;
	int		wid;
	t_pt	**points;
	t_vec3	**points_proj;
	float	fur;
	float	clo;
}	t_map;

typedef struct s_transform
{
	float	scale;
	float	depth_scale;
	t_vec3	offset;
	t_vec3	rotations;
	int		rotate;
	int		project;
	t_mat3	z_rot;
	t_mat3	y_rot;
	t_mat3	x_rot;
}	t_transform;

typedef struct s_cam
{
	float	near;
	float	far;
	float	fov;
	t_mat4	mat;
	//maybe pos/rot
}	t_cam;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_cam		cam;
	t_data		img;
	t_transform	transform;
	int			display_mode;
	int			projection;
}	t_vars;


void				pixel_put(t_data *data, int x, int y, unsigned int color);
void				draw_line(t_vars *vars, t_pt p0, t_pt p1);

t_pt				get_transformed_point(t_vars *vars, int x, int y);
t_vec3				project_pos(t_vars *vars, t_vec3 pos);

int					count_points(char const *s, char c);
char				**ft_split(char const *s, char c);
void				ft_free_split(char **split);

void				*ft_memcpy(void *dest, const void *src, size_t n);
size_t				ft_strlen(const char *s);

int					ft_atoi(const char *nptr);
unsigned int		ft_atoui(const char *nptr);

char				*read_map(int fd, t_vars *vars);
void				parse_map(t_vars *vars, char *map_str);

void				free_map(t_vars *vars);
void				free_mlx(t_vars *vars);
void				free_and_exit1(t_vars *vars, void *line, void *map_str);

void				update_depth(int change, t_vars *vars);
void				update_zoom(int change, t_vars *vars);
void				move_grid(int x, int y, t_vars *vars);
void				rotate_grid_z(int rotation, t_vars *vars);
void				rotate_grid_x(int rotation, t_vars *vars);
int					key_hook(int keycode, t_vars *vars);
int					close_all(t_vars *vars);

float				dmap(float v, float min, float max);

t_vec3				mult_vec3_mat3(t_vec3 vec, t_mat3 mat);
t_vec3				isometric_projection(t_vec3 vec, t_vars *vars);
t_vec3				mult_vec3_mat4(t_vec3 in, t_mat4 m);
void				set_projection_matrix(t_cam *cam);

#endif
