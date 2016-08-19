/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_matrices.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 16:10:35 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 16:10:36 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat44	new_rotation_mat44(const int type, t_f64 angle)
{
	t_mat44	mat;

	mat = new_translation_mat44();
	if (type == ROTATE_X)
	{
		mat.mat[1][1] = cos(angle);
		mat.mat[2][2] = mat.mat[1][1];
		mat.mat[1][2] = -1 * sin(angle);
		mat.mat[2][1] = -1 * mat.mat[1][2];
	}
	else if (type == ROTATE_Y)
	{
		mat.mat[0][0] = cos(angle);
		mat.mat[2][2] = mat.mat[0][0];
		mat.mat[0][2] = sin(angle);
		mat.mat[2][0] = -1 * mat.mat[0][2];
	}
	else if (type == ROTATE_Z)
	{
		mat.mat[0][0] = cos(angle);
		mat.mat[1][1] = mat.mat[0][0];
		mat.mat[0][1] = -1 * sin(angle);
		mat.mat[1][0] = -1 * mat.mat[0][1];
	}
	return (mat);
}

t_mat44	new_orientation_mat44(t_vec3f rot_vec)
{
	t_mat44	mat_x;
	t_mat44	mat_y;
	t_mat44	mat_z;
	t_mat44	mat_xyz;

	mat_x = new_rotation_mat44(ROTATE_X, rot_vec.x);
	mat_y = new_rotation_mat44(ROTATE_Y, rot_vec.y);
	mat_z = new_rotation_mat44(ROTATE_Z, rot_vec.z);
	mat_xyz = multiply_mat44(mat_x, mat_y);
	mat_xyz = multiply_mat44(mat_xyz, mat_z);
	kill_matrix(&mat_x);
	kill_matrix(&mat_y);
	kill_matrix(&mat_z);
	return (mat_xyz);
}

t_mat44	new_transform_mat44(const int type, t_vec3f v)
{
	t_mat44	mat;

	mat = new_translation_mat44();
	if (type == SCALE)
	{
		mat.mat[0][0] = v.x;
		mat.mat[1][1] = v.y;
		mat.mat[2][2] = v.z;
		mat.mat[3][3] = 1;
	}
	else if (type == TRANSLATE)
	{
		mat.mat[0][3] = v.x;
		mat.mat[1][3] = v.y;
		mat.mat[2][3] = v.z;
		mat.mat[3][3] = 1;
	}
	return (mat);
}
