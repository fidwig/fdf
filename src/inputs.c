/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:42:07 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/27 16:08:26 by jsommet          ###   ########.fr       */
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
	vars->transform.scale += change * 0.5;
}

void	move_grid(int x, int y, t_vars *vars)
{
	vars->transform.offset.x += x;
	vars->transform.offset.y += y;
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
	move_grid((keycode == XK_d) - (keycode == XK_a),
		(keycode == XK_s) - (keycode == XK_w), vars);
	rotate_grid_x((keycode == XK_Up) - (keycode == XK_Down), vars);
	rotate_grid_z((keycode == XK_Right) - (keycode == XK_Left), vars);
	change_ffov((keycode == XK_o) - (keycode == XK_i), vars);
	vars->display_mode += (keycode == XK_m);
	if (vars->display_mode > 2)
		vars->display_mode = 0;
	vars->projection += (keycode == XK_p);
	if (vars->projection > 1)
		vars->projection = 0;
	if (keycode == XK_l)
		vars->transform.rotations = (t_vec3){50, 0, 45};
	return (0);
}
