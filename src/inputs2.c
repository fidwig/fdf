/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:56:04 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/27 13:43:23 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_grid_z(int rotation, t_vars *vars)
{
	vars->transform.rotate = 1;
	vars->transform.project = 1;
	vars->transform.rotations.z += rotation;
}

void	rotate_grid_x(int rotation, t_vars *vars)
{
	vars->transform.rotate = 1;
	vars->transform.project = 1;
	vars->transform.rotations.x += rotation;
}

void	change_ffov(int value, t_vars *vars)
{
	vars->transform.project = 1;
	vars->cam.fov += value * 0.1;
	if (fabs(vars->cam.fov) < 0.1)
		vars->cam.fov = 0.1 * value;
	vars->cam.far = -vars->cam.fov * (vars->map.hei + vars->map.wid);
	vars->cam.near = 0;
}

//not input related but i dont have room in other files

t_color	ui2c(unsigned int cui)
{
	t_color	c;

	c.b = cui & 0xFF;
	c.g = (cui >> 8) & 0xFF;
	c.r = (cui >> 16) & 0xFF;
	c.t = (cui >> 24) & 0xFF;
	return (c);
}

unsigned int	c2ui(t_color c)
{
	unsigned int	cui;

	cui = (c.t << 24 | c.r << 16 | c.g << 8 | c.b);
	return (cui);
}
