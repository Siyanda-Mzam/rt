

#include "matrix.h"

t_mat	had_multiply_mat44(t_mat a, t_mat b)
{
	t_mat44	mat;
	int		i;
	int		j;

	i = 0;
	mat = new_mat44(1);
	while (i < a.rows)
	{
		j = 0;
		while (j < a.cols)
		{
			mat.mat[i][j] = a.mat[i][j] * b.mat[i][j];
			j++;
		}
		i++;
	}
	return (mat);
}
