/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:53:15 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 16:42:58 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static inline void	inner_op(int i, t_mat temp, t_mat id)
{
	t_f64	t;
	int		j;

	j = 0;
	while (j < 4)
	{
		if (j != i)
		{
			t = temp.mat[j][i];
			sub_row(temp, j, i, t);
			sub_row(id, j, i, t);
		}
		j++;
	}
}

t_mat				inverse_mat44(t_mat44 mat)
{
	int		i;
	int		j;
	t_f64	t;
	t_mat44	temp;
	t_mat44	identity;

	i = 0;
	temp = dup_mat(&mat);
	identity = new_translation_mat44();
	while (i != 4)
	{
		j = get_row(temp, i);
		if (j != i)
		{
			swap_rows(temp, i, j);
			swap_rows(identity, i, j);
		}
		t = temp.mat[i][i];
		divide_row(temp, i, t);
		divide_row(identity, i, t);
		inner_op(i++, temp, identity);
	}
	kill_matrix(&temp);
	kill_matrix(&mat);
	return (identity);
}
