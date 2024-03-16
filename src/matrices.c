/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/16 17:09:14 by jsommet          ###   ########.fr       */
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

// void	set_projection_matrix(t_cam *cam)
// {
// 	float	scale;
// 	t_mat4	m;

// 	//near = near clipping plane
// 	//far = far clipping plane
//     // set the basic projection matrix
// 	scale = 1 / tan(cam->fov * 0.5 * M_PI / 180);
// 	// scale the x coordinates of the projected point
// 	m.a = (t_vec4){scale, 0, 0, 0};
// 	// scale the y coordinates of the projected point
// 	m.b = (t_vec4){0, scale, 0, 0};
// 	// used to remap z to [0,1] and set w = -z;
// 	m.c = (t_vec4){0, 0, -cam->far / (cam->far - cam->near), -1};
// 	// used to remap z [0,1]
// 	m.d = (t_vec4){0, 0, -cam->far * cam->near / (cam->far - cam->near), 0};

// 	cam->mat = m;
// }

// t_vec3	mult_vec3_mat4(t_vec3 in, t_mat4 m)
// {
// 	t_vec3	out;
// 	float	w;

// 	out.x = in.x * m.a.x + in.y * m.b.x + in.z * m.c.x + m.d.x;
// 	out.y = in.x * m.a.y + in.y * m.b.y + in.z * m.c.y + m.d.y;
// 	out.z = in.x * m.a.z + in.y * m.b.z + in.z * m.c.z + m.d.z;
// 	w = in.x * m.a.w + in.y * m.b.w + in.z * m.c.w + m.d.w;

//     // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
// 	if (w != 1)
// 	{
// 		out.x /= w;
// 		out.y /= w;
// 		out.z /= w;
// 	}
// 	return (out);
// }
