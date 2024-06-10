/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/06/07 16:53:23 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat3	z_rotation_matrix(float deg)
{
	t_mat3	mat;

	deg = (deg * M_PI) / 180.0;
	mat.a = (t_vec3){cos(deg), sin(deg), 0};
	mat.b = (t_vec3){-sin(deg), cos(deg), 0};
	mat.c = (t_vec3){0, 0, 1};
	return (mat);
}

t_mat3	x_rotation_matrix(float deg)
{
	t_mat3	mat;

	deg = (deg * M_PI) / 180.0;
	mat.a = (t_vec3){1, 0, 0};
	mat.b = (t_vec3){0, cos(deg), sin(deg)};
	mat.c = (t_vec3){0, -sin(deg), cos(deg)};
	return (mat);
}

t_vec3	mult_vec3_mat3(t_vec3 vec, t_mat3 mat)
{
	t_vec3	result;

	result.x = vec.x * mat.a.x + vec.y * mat.b.x + vec.z * mat.c.x;
	result.y = vec.x * mat.a.y + vec.y * mat.b.y + vec.z * mat.c.y;
	result.z = vec.x * mat.a.z + vec.y * mat.b.z + vec.z * mat.c.z;
	return (result);
}
