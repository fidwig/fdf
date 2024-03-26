/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:38 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/22 18:55:54 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_points(t_vars *vars)
{
	int		x;
	int		y;
	t_vec3	p_pos;

	if (!vars->transform.project)
		return ;
	y = 0;
	while (y < vars->map.hei)
	{
		x = 0;
		while (x < vars->map.wid)
		{
			p_pos = project_pos(vars, vars->map.points[y][x].pos);
			if (y + x == 0 || p_pos.z > vars->map.clo)
				vars->map.clo = p_pos.z;
			if (y + x == 0 || p_pos.z < vars->map.fur)
				vars->map.fur = p_pos.z;
			vars->map.points_proj[y][x] = p_pos;
			x++;
		}
		y++;
	}
}

t_vec3	isometric_projection(t_vec3 vec, t_vars *vars)
{
	t_mat3	mat;

	if (vars->transform.rotate)
		vars->transform.z_rot = z_rotation_matrix(vars->transform.rotations.z);
	mat = vars->transform.z_rot;
	vec = mult_vec3_mat3(vec, mat);
	if (vars->transform.rotate)
		vars->transform.x_rot = x_rotation_matrix(vars->transform.rotations.x);
	mat = vars->transform.x_rot;
	vec = mult_vec3_mat3(vec, mat);
	vars->transform.rotate = 0;
	return (vec);
}

t_vec3	project_pos(t_vars *vars, t_vec3 pos)
{
	float	r;

	pos.z = pos.z * vars->transform.depth_scale;
	pos = isometric_projection(pos, vars);
	pos.x += vars->transform.offset.x;
	pos.y += vars->transform.offset.y;
	if (vars->projection == 1)
	{
		r = dmap(pos.z, vars->cam.far, vars->cam.near);
		pos.x *= r;
		pos.y *= r;
	}
	return (pos);
}

t_pt	get_transformed_point(t_vars *vars, int x, int y)
{
	t_pt	pt;

	pt.pos = vars->map.points_proj[y][x];
	pt.pos.x = pt.pos.x * vars->transform.scale + CENTER_X;
	pt.pos.y = pt.pos.y * vars->transform.scale + CENTER_Y;
	pt.col = vars->map.points[y][x].col;
	return (pt);
}
