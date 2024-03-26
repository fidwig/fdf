/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:12:45 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/26 14:59:38 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_projected_points(t_vars *vars)
{
	int					y;
	int					x;
	t_pt				pt;
	t_pt				apt;

	y = -1;
	while (++y < vars->map.hei)
	{
		x = -1;
		while (++x < vars->map.wid)
		{
			pt = get_transformed_point(vars, x, y);
			if (x < vars->map.wid - 1)
			{
				apt = get_transformed_point(vars, x + 1, y);
				draw_line(vars, pt, apt);
			}
			if (y < vars->map.hei - 1)
			{
				apt = get_transformed_point(vars, x, y + 1);
				draw_line(vars, pt, apt);
			}
		}
	}
}

void	clear_image(t_data *image, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			pixel_put(image, i, j, color);
			j++;
		}
		i++;
	}
}

void	soft_slope(t_vars *vars, t_line_vars v)
{
	float			c[2];
	float			x;
	float			y;
	int				i;
	unsigned int	col;

	x = v.p0.pos.x;
	y = v.p0.pos.y;
	c[0] = sign(v.dx);
	c[1] = v.dy / fabs(v.dx);
	i = 0;
	while (i <= fabs(v.dx))
	{
		if (out_of_display(x, y, c[0], c[1]))
			return ;
		col = blend_colors(v.p0.col, v.p1.col, (float)i / fabs(v.dx));
		col = dep(vars, col, dmap(v.p0.pos.z, vars->map.fur, vars->map.clo));
		pixel_put(&vars->img, (int)x, (int)y, col);
		x += c[0];
		y += c[1];
		i++;
	}
}

void	hard_slope(t_vars *vars, t_line_vars v)
{
	float			c[2];
	float			x;
	float			y;
	int				i;
	unsigned int	col;

	x = v.p0.pos.x;
	y = v.p0.pos.y;
	c[0] = v.dx / fabs(v.dy);
	c[1] = sign(v.dy);
	i = 0;
	while (i <= fabs(v.dy))
	{
		if (out_of_display(x, y, c[0], c[1]))
			return ;
		col = blend_colors(v.p0.col, v.p1.col, (float)i / fabs(v.dy));
		col = dep(vars, col, dmap(v.p0.pos.z, vars->map.fur, vars->map.clo));
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
		soft_slope(vars, (t_line_vars){p0, p1, d[0], d[1]});
	else if (fabs(d[1]) > fabs(d[0]))
		hard_slope(vars, (t_line_vars){p0, p1, d[0], d[1]});
}
