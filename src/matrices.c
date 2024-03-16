/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/16 03:00:54 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat3	z_rotation_matrix(float deg)
{
	t_mat3	mat;

	deg = (deg * M_PI) / 180.0;
	mat.a = (t_vec3){cos(deg), -sin(deg), 0};
	mat.b = (t_vec3){sin(deg), cos(deg), 0};
	mat.c = (t_vec3){0, 0, 1};
	return (mat);
}

t_mat3	x_rotation_matrix(float deg)
{
	t_mat3	mat;

	deg = (deg * M_PI) / 180.0;
	mat.a = (t_vec3){1, 0, 0};
	mat.b = (t_vec3){0, cos(deg), -sin(deg)};
	mat.c = (t_vec3){0, sin(deg), cos(deg)};
	return (mat);
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
