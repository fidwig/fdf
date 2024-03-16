/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:56:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/03/16 03:48:53 by jsommet          ###   ########.fr       */
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


/*
PERSPECTIVE PROJECTION MATRICE IG

void setProjectionMatrix(float fov, float near, float far, t_mat44 M)
{
	//near = near clipping plane
	//far = far clipping plane
    // set the basic projection matrix
    float scale = 1 / tan(fov * 0.5 * M_PI / 180);
    M.a.x = scale;  // scale the x coordinates of the projected point
    M.b.y = scale;  // scale the y coordinates of the projected point
    M.c.z = -far / (far - near);  // used to remap z to [0,1]
    M.d.z = -far * near / (far - near);  // used to remap z [0,1]
    M.c.w = -1;  // set w = -z 
    M.d.w, etc = 0;
	//all the other values are 0
}
 
t_vec3 mult_vec3_mat44(t_vec3 in, t_mat44 M) 
{ 
	t_vec3 out;

    //out = in * M;
    out.x   = in.x * M.a.x + in.y * M.b.x + in.z * M.c.x + M.d.x; 
    out.y   = in.x * M.a.y + in.y * M.b.y + in.z * M.c.y + M.d.y; 
    out.z   = in.x * M.a.z + in.y * M.b.z + in.z * M.c.z + M.d.z; 
    float w = in.x * M.a.w + in.y * M.b.w + in.z * M.c.w + M.d.w; 
 
    // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
    if (w != 1) { 
        out.x /= w; 
        out.y /= w; 
        out.z /= w; 
    } 
	return (out);
} 
*/
