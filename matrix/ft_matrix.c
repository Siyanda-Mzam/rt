/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:50:17 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:50:52 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static t_f64	**new_2d_arr(int r, int c, int dvalue)
{
	t_f64	**arr;
	int		j;
	int		k;

	j = 0;
	if (!(arr = (t_f64**)malloc(sizeof(t_f64*) * r)))
		return (NULL);
	while (j < r)
	{
		k = 0;
		arr[j] = (t_f64*)malloc(sizeof(t_f64) * c + 1);
		if (arr[j] == NULL)
			return (NULL);
		while (k < c)
		{
			arr[j][k] = dvalue;
			k++;
		}
		j++;
	}
	return (arr);
}

t_mat			new_mat(int r, int v, t_f64 dv)
{
	static int	cnt = 0;
	t_mat		mat;
	t_f64		**arr;

	cnt = cnt + 1;
	arr = new_2d_arr(r, v, dv);
	mat.mat = arr;
	mat.rows = r;
	mat.cols = v;
	mat.age = cnt;
	mat.id = cnt;//(t_i32)arr;
	garbage_collector(mat);
	return (mat);
}

t_mat44			new_mat44(t_f64 f)
{
	return ((t_mat44)new_mat(4, 4, f));
}

t_mat44			new_translation_mat44(void)
{
	int		c;
	t_mat	m;

	m = new_mat44(0);
	c = 0;
	while (c < 4)
	{
		m.mat[c][c] = 1;
		c++;
	}
	return (m);
}

void			kill_matrix(t_mat *mat)
{
	int	r;

	r = 0;
	if (mat->mat != NULL)
	{
		while (r < mat->rows)
		{
			free(mat->mat[r]);
			r++;
		}
		free(mat->mat);
		manual_dispose(mat);
	}
}
