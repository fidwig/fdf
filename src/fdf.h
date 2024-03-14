/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:04:50 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/14 19:38:39 by jsommet          ###   ########.fr       */
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

# define CENTER_X 		WIDTH/2
# define CENTER_Y 		HEIGHT/2
# define SCALE 			5
# define DEPTH_SCALE	0.1

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
}	t_map;

typedef struct s_transform
{
	float	scale;
	float	depth_scale;
	t_vec3	offset;
	t_vec3	rotations;
	t_vec3	prev_rots;
	t_mat3	z_rot;
	t_mat3	y_rot;
	t_mat3	x_rot;
}	t_transform;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_data		img;
	t_transform	transform;
}	t_vars;


void				pixel_put(t_data *data, int x, int y, unsigned int color);
void				draw_line(t_vars *vars, t_pt p0, t_pt p1);

t_pt				get_screenspace_pos(t_vars *vars, t_pt pt);

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

t_vec3				mult_vec3_mat3(t_vec3 vec, t_mat3 mat);
t_vec3				isometric_projection(t_vec3 vec, t_vars *vars);

#endif
