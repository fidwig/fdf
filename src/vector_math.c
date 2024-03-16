/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:38 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/16 19:28:00 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	mult_vec3_mat3(t_vec3 vec, t_mat3 mat)
{
	t_vec3	result;

	result.x = vec.x * mat.a.x + vec.y * mat.b.x + vec.z * mat.c.x;
	result.y = vec.x * mat.a.y + vec.y * mat.b.y + vec.z * mat.c.y;
	result.z = vec.x * mat.a.z + vec.y * mat.b.z + vec.z * mat.c.z;

	return (result);
}

float	signf(float n)
{
	return ((float)(n >= 0) * 2 - 1);
}

t_vec3	project_pos(t_vars *vars, t_vec3 pos)
{
	float	r;

	pos.z = pos.z * vars->transform.depth_scale;
	pos = isometric_projection(pos, vars);
	// printf("%f %f %f\n", pos.x, pos.y, pos.z);

	pos.x += vars->transform.offset.x;
	pos.y += vars->transform.offset.y;

	// pos = mult_vec3_mat4(pos, vars->cam.mat);
	// float	nearcp = 3 * (vars->map.hei > vars->map.wid ? vars->map.hei : vars->map.wid);
	//		nearcp -> far/near clipping plane
	// float cz = -cam->far / (cam->far - cam->near);
	// float dz = -cam->far * cam->near / (cam->far - cam->near);
	if (vars->projection == 1)
	{
		r = dmap(pos.z, vars->cam.far, 0);//vars->cam.near);
		pos.y *= r;
		pos.x *= r;
	}

	return (pos);
}

t_pt	get_transformed_point(t_vars *vars, int x, int y)
{
	t_pt	pt;

	pt.pos = vars->map.points_proj[y][x];

	// pt.pos.x += vars->transform.offset.x / vars->transform.scale;
	// pt.pos.y += vars->transform.offset.y / vars->transform.scale;

	pt.pos.x = pt.pos.x * vars->transform.scale + CENTER_X;// + vars->transform.offset.x;
	pt.pos.y = pt.pos.y * vars->transform.scale + CENTER_Y;// + vars->transform.offset.y;
	pt.col = vars->map.points[y][x].col;
	return (pt);
}
