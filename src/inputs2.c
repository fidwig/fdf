/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:56:04 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/26 15:01:03 by jsommet          ###   ########.fr       */
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
