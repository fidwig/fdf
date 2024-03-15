/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:12:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/15 21:48:45 by jsommet          ###   ########.fr       */
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
	if (col.t > p_col.t || (*(unsigned int *)dst) == BLACK || color == BLACK)
		*(unsigned int *)dst = color;
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

float	dmap(float v, float min, float max)
{
	if (max == min)
		return (0);
	v = (v - min) / (max - min);
	return (v);
}

//encode depth into color
//CANT NAME IT BECAUSE OF THE FUCKING NORMINETTE I HATE IT SO MUCH
unsigned int	dep(t_vars *vars, unsigned int color, float depth)
{
	t_color	trgb;

	trgb = *((t_color *) &color);
	trgb.t = (unsigned char) 255 * depth;
	if (vars->display_mode == 1)
	{
		trgb.r = 255 * depth;
		trgb.g = 255 * depth;
		trgb.b = 255 * depth;
	}
	else if (vars->display_mode == 2)
	{
		trgb.r *= depth;
		trgb.g *= depth;
		trgb.b *= depth;
	}
	return (*((unsigned int *) &trgb));
}

void	soft_slope(t_vars *vars, float dx, float dy, t_pt p0, t_pt p1)
{
	float			c[2];
	float			x;
	float			y;
	int				i;
	unsigned int	col;

	x = p0.pos.x;
	y = p0.pos.y;
	c[0] = sign(dx);
	c[1] = dy / fabs(dx);
	i = 0;
	while (i <= fabs(dx))
	{
		col = blend_colors(p0.col, p1.col, (float)i / fabs(dx));
		col = dep(vars, col, dmap(p0.pos.z, vars->map.fur, vars->map.clo));
		pixel_put(&vars->img, (int)x, (int)y, col);
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
	unsigned int	col;

	x = p0.pos.x;
	y = p0.pos.y;
	c[0] = dx / fabs(dy);
	c[1] = sign(dy);
	i = 0;
	while (i <= fabs(dy))
	{
		col = blend_colors(p0.col, p1.col, (float)i / fabs(dy));
		col = dep(vars, col, dmap(p0.pos.z, vars->map.fur, vars->map.clo));
		pixel_put(&vars->img, (int)x, (int)y, col);
		x += c[0];
		y += c[1];
		i++;
	}
}

//draws line from point p0 to point p1
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
