/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:51:52 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:52:48 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat	transpose_mat(t_mat *m)
{
	t_mat	mat;
	int		i;
	int		j;

	i = 0;
	mat = new_mat(m->cols, m->rows, 0);
	if (mat.mat == NULL)
		perror("Matrix: Error matrix creation\n");
	while (i < m->rows)
	{
		j = 0;
		while (j < m->cols)
		{
			mat.mat[j][i] = m->mat[i][j];
			j++;
		}
		i++;
	}
	return (mat);
}

t_mat44	multiply_mat44(t_mat44 a, t_mat44 b)
{
	t_mat44	temp;
	t_i32	i;
	t_i32	j;
	t_i32	k;

	i = 0;
	temp = new_translation_mat44(0);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			if (i == j)
				temp.mat[i][j]--;
			while (k < 4)
			{
				temp.mat[i][j] += a.mat[i][k] * b.mat[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (temp);
}

t_vec3f	vector_multiply(t_vec3f v, t_mat44 m)
{
	t_f64	a;
	t_f64	b;
	t_f64	c;
	t_f64	w;
	t_vec3f	dst;

	a = v.x * m.mat[0][0] + v.y * m.mat[1][0] + v.z * m.mat[2][0];
	b = v.x * m.mat[0][1] + v.y * m.mat[1][1] + v.z * m.mat[2][1];
	c = v.x * m.mat[0][2] + v.y * m.mat[1][2] + v.z * m.mat[2][2];
	w = v.x * m.mat[0][3] + v.y * m.mat[1][3] + v.z * m.mat[2][3];
	a += m.mat[3][0];
	b += m.mat[3][1];
	c += m.mat[3][2];
	w += m.mat[3][3];
	dst.x = w != 0 ? a / w : 0;
	dst.y = w != 0 ? b / w : 0;
	dst.z = w != 0 ? c / w : 0;
	return (dst);
}

t_vec3f	vector_dir_multiply(t_vec3f v, t_mat44 m)
{
	t_vec3f	dst;

	dst.x = v.x * m.mat[0][0] + v.y * m.mat[1][0] + v.z * m.mat[2][0];
	dst.y = v.x * m.mat[0][1] + v.y * m.mat[1][1] + v.z * m.mat[2][1];
	dst.z = v.x * m.mat[0][2] + v.y * m.mat[1][2] + v.z * m.mat[2][2];
	dst.x += m.mat[3][0];
	dst.y += m.mat[3][1];
	dst.z += m.mat[3][2];
	return (dst);
}
