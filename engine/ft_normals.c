/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:23:00 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 16:46:33 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_vec3f	sphere_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 tmat)
{
	t_vec3f	nhit;

	(void)tmat;
	nhit = sub_vec3f(phit, pos);
	return (normal_vec3f(&nhit));
}

t_vec3f	cylinder_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 tmat)
{
	static t_mat	tr = {0, 0, 0, 0, 0};
	t_vec3f			nhit;
	t_vec3f			pr;

	if (tr.mat == 0)
		tr = transpose_mat(&tmat);
	pr = vector_dir_multiply(*phit, tmat);
	nhit = sub_vec3f(&pr, pos);
	nhit.y = 0;
	return normalize_vec3f((vector_dir_multiply(normal_vec3f(&nhit), tr)));
}

t_vec3f	cone_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 tmat)
{
	t_vec3f	nhit;
	t_vec3f	pr;
	t_vec3f del;
	t_vec3f	tmp;

	pr = vector_dir_multiply(*phit, tmat);
	tmp = new_vec3f(0, -1, 0);
	nhit = sub_vec3f(&pr, pos);
	del = cross_vec3f(&tmp, &nhit);
	return (normalize_vec3f(cross_vec3f(&nhit, &del)));
}

t_vec3f	plane_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 tmat)
{
	t_vec3f	nhit;

	(void)phit;
	(void)tmat;
	nhit = dup_vec3f(pos);
	return ((normalize_vec3f(nhit)));
}
