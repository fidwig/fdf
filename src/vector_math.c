/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:38 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/15 20:22:04 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// t_vec3	multiply_vec3_mat3(t_vec3 vec, float **matrix, int wid, int hei)
// {
// 	return (vec);
// }

t_vec3	mult_vec3_mat3(t_vec3 vec, t_mat3 mat)
{
	t_vec3	result;

	result.x = vec.x * mat.a.x + vec.y * mat.a.y + vec.z * mat.a.z;
	result.y = vec.x * mat.b.x + vec.y * mat.b.y + vec.z * mat.b.z;
	result.z = vec.x * mat.c.x + vec.y * mat.c.y + vec.z * mat.c.z;

	return (result);
}

t_vec3	project_pos(t_vars *vars, t_vec3 pos)
{
	pos.z = pos.z * vars->transform.depth_scale;
	pos = isometric_projection(pos, vars);
	return (pos);
}

t_pt	get_transformed_point(t_vars *vars, int x, int y)
{
	t_pt	pt;

	// pt.pos = project_pos(vars, vars->map.points[y][x].pos);
	pt.pos = vars->map.points_proj[y][x];

	pt.pos.x = pt.pos.x * vars->transform.scale + vars->transform.offset.x;
	pt.pos.y = pt.pos.y * vars->transform.scale + vars->transform.offset.y;
	pt.col = vars->map.points[y][x].col;
	return (pt);
}
