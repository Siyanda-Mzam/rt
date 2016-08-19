/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 14:11:31 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:56:23 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include <vector.h>
# include <stdio.h>

enum	e_transformations
{
	ROTATE_X,
	ROTATE_Y,
	ROTATE_Z,
	SCALE,
	TRANSLATE
};

typedef struct		s_matrix
{
	t_f64		**mat;
	t_i32		rows;
	t_i32		cols;
	t_i32		id;
	int			age;
}					t_matrix;

typedef t_matrix	t_matrix44;
typedef t_matrix	t_mat;
typedef t_matrix	t_mat44;

t_mat44				new_translation_mat44();
t_mat44				inverse_mat44(t_mat44 mat);
t_mat44				new_mat44(t_f64 dvalue);
t_mat44				new_rotation_mat44(const int type, t_f64 angle);
t_mat44				new_orientation_mat44(t_vec3f rot_vec);
t_vec3f				vector_multiply(t_vec3f v, t_mat44 m);
t_vec3f				vector_dir_multiply(t_vec3f b, t_mat44 m);
t_mat				transpose_mat(t_mat *m);
t_mat				had_multiply_mat44(t_mat a, t_mat b);
t_mat				multiply_mat44(t_mat a, t_mat b);
t_mat				dup_mat(t_mat *src);
t_mat				new_mat(int r, int c, t_f64 dvalue);
void				cpy_mat(t_mat *dst, t_mat *src);
void				set_row(t_mat44 m, const int r, const t_f64 *a);
void				set_col(t_mat44 m, const int c, const t_f64 *a);
void				kill_matrix(t_mat *mat);
void				garbage_collector(t_mat44 m);
void				dispose_garbage();
void				manual_dispose(t_mat *m);
void				ft_swap(t_f64 *a, t_f64 *b);
void				swap_rows(t_mat mat, int i, int j);
void				divide_row(t_mat m, int i, t_f64 temp);
void				sub_row(t_mat m, int i, int j, t_f64 temp);
int					get_row(t_mat m, int i);
#endif
