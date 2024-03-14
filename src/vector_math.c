/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:38 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/14 19:23:35 by jsommet          ###   ########.fr       */
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

// t_vec3	mult_vec3_mat3(t_vec3 vec, t_mat3 mat)
// {
// 	t_vec3	result;

// 	result.x = vec.x * mat.a.x + vec.y * mat.b.x + vec.z * mat.c.x;
// 	result.y = vec.x * mat.a.y + vec.y * mat.b.y + vec.z * mat.c.y;
// 	result.z = vec.x * mat.a.z + vec.y * mat.b.z + vec.z * mat.c.z;

// 	return (result);
// }

t_pt	get_screenspace_pos(t_vars *vars, t_pt pt)
{
	t_pt	screenspace_point;
	t_vec3	vec;

	vec = pt.pos;
	vec.z = vec.z * vars->transform.depth_scale;

	vec = isometric_projection(vec, vars);

	vec.x = vec.x * vars->transform.scale + vars->transform.offset.x;
	vec.y = vec.y * vars->transform.scale + vars->transform.offset.y;
	screenspace_point.pos = vec;
	screenspace_point.col = pt.col;
	return (screenspace_point);
}
