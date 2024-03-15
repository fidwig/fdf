/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:42:07 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/15 21:44:36 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	update_depth(int change, t_vars *vars)
{
	vars->transform.project = 1;
	vars->transform.depth_scale += change * 0.01;
}

void	update_zoom(int change, t_vars *vars)
{
	vars->transform.scale += change * 0.1;
}

void	move_grid(int x, int y, t_vars *vars)
{
	vars->transform.offset.x += x * 5;
	vars->transform.offset.y += y * 5;
}

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

int	close_all(t_vars *vars)
{
	free_mlx(vars);
	free_map(vars);
	exit (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		close_all(vars);
	update_depth((keycode == XK_x) - (keycode == XK_z), vars);
	update_zoom((keycode == XK_v) - (keycode == XK_c), vars);
	move_grid((keycode == XK_d) - (keycode == XK_a), (keycode == XK_s) - (keycode == XK_w), vars);
	rotate_grid_x((keycode == XK_Up) - (keycode == XK_Down), vars);
	rotate_grid_z((keycode == XK_Right) - (keycode == XK_Left), vars);
	vars->display_mode += (keycode == XK_m);
	if (vars->display_mode > 2)
		vars->display_mode = 0;
	return (0);
}
