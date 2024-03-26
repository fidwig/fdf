/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:27:38 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/26 14:52:57 by jsommet          ###   ########.fr       */
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
//CANT NAME IT PROPERLY BECAUSE OF THE FUCKING NORMINETTE I HATE IT SO MUCH
unsigned int	dep(t_vars *vars, unsigned int color, float depth)
{
	t_color	trgb;

	trgb = *((t_color *) &color);
	trgb.t = (unsigned char) 255 * depth;
	if (vars->display_mode == 1)
	{
		trgb.r = 254 * depth + 1;
		trgb.g = 254 * depth + 1;
		trgb.b = 254 * depth + 1;
	}
	else if (vars->display_mode == 2)
	{
		trgb.r = (trgb.r - 1) * depth + 1;
		trgb.g = (trgb.g - 1) * depth + 1;
		trgb.b = (trgb.b - 1) * depth + 1;
	}
	return (*((unsigned int *) &trgb));
}
