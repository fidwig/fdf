/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:12:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/14 19:11:44 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;
	t_color	col;
	t_color	p_col;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bit_depth / 8));
	col = *((t_color *) &color);
	p_col = *((t_color *) dst);
	if ((col.t > p_col.t) || col.t == 0)
		*(unsigned int *)dst = color;
	// *(unsigned int *)dst = color;
}

unsigned int	blend_colors(unsigned int c0, unsigned int c1, float ratio)
{
	t_color	col0;
	t_color	col1;

	col0 = *((t_color *) &c0);
	col1 = *((t_color *) &c1);
	col0.r = ((float)col1.r * ratio) + ((float)col0.r * (1 - ratio));
	col0.g = ((float)col1.g * ratio) + ((float)col0.g * (1 - ratio));
	col0.b = ((float)col1.b * ratio) + ((float)col0.b * (1 - ratio));
	return (*((unsigned int *) &col0));
}

int	sign(int n)
{
	return (((n >= 0) * 2 - 1) * (n != 0));
}

int	maximum(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

unsigned char	get_depth_value(int y, t_vars *vars)
{
	float			depth01;

	y += (maximum(vars->map.hei, vars->map.wid)) / 2;
	depth01 = y / maximum(vars->map.hei, vars->map.wid);
	if (depth01 > 0.9)
		depth01 = 0.9;
	if (depth01 < 0.0)
		depth01 = 0.0;
	return ((unsigned char)(255 * depth01));
}

void	soft_slope(t_vars *vars, float dx, float dy, t_pt p0, t_pt p1)
{
	float			c[2];
	float			x;
	float			y;
	int				i;
	unsigned int	color;

	x = p0.pos.x;
	y = p0.pos.y;
	c[0] = sign(dx);
	c[1] = dy / fabs(dx);
	i = 0;
	while (i < fabs(dx))
	{
		color = blend_colors(p0.col, p1.col, (float)i / fabs(dx));
		// ((t_color *) &color)->t = get_depth_value(maximum(p0.pos.y, p1.pos.y), vars);
		pixel_put(&vars->img, (int)x, (int)y, color);
		x += c[0];
		y += c[1];
		i++;
	}
}

void	hard_slope(t_vars *vars, float dx, float dy, t_pt p0, t_pt p1)
{
	float			c[2];
	float			x;
	float			y;
	int				i;
	unsigned int	color;

	x = p0.pos.x;
	y = p0.pos.y;
	c[0] = dx / fabs(dy);
	c[1] = sign(dy);
	i = 0;
	while (i < fabs(dy))
	{
		color = blend_colors(p0.col, p1.col, (float)i / fabs(dy));
		// ((t_color *) &color)->t = get_depth_value(maximum(p0.pos.y, p1.pos.y), vars);
		pixel_put(&vars->img, (int)x, (int)y, color);
		x += c[0];
		y += c[1];
		i++;
	}
}

void	draw_line(t_vars *vars, t_pt p0, t_pt p1)
{
	float	d[2];

	d[0] = p1.pos.x - p0.pos.x;
	d[1] = p1.pos.y - p0.pos.y;
	if (fabs(d[0]) >= fabs(d[1]))
		soft_slope(vars, d[0], d[1], p0, p1);
	else if (fabs(d[1]) > fabs(d[0]))
		hard_slope(vars, d[0], d[1], p0, p1);
}

// void	draw_line(t_vars *vars, t_screenspace_point p0, t_screenspace_point p1)
// {
// 	int		d[2];
// 	int		x;
// 	int		y;
// 	int		i;
// 	int		j;
// 	int		c[2];
// 	int		p;

// 	x = p0.x;
// 	y = p0.y;
// 	d[0] = p1.x - p0.x;
// 	d[1] = p1.y - p0.y;
// 	c[0] = sign(d[0]);
// 	c[1] = sign(d[1]);
// 	d[0] = abs(d[0]);
// 	d[1] = abs(d[1]);
// 	p = 2 * d[1] - d[0];
// 	i = 0;
// 	j = 0;
// 	while (1)
// 	{
// 		pixel_put(&vars->img, (int)x, (int)y, p0.color);
// 		if (i == d[0] && j == d[1])
// 			break ;
// 		if (i != d[0])
// 		{
// 			x += c[0];
// 			i++;
// 		}
// 		if (p < 0)
// 			p += 2 * d[1];
// 		else
// 		{
// 			p += 2 * (d[1] - d[0]);
// 			y += c[1];
// 			if (j != d[1])
// 				j++;
// 		}
// 	}
// }
