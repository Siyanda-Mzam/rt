/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:23:00 by smamba            #+#    #+#             */
/*   Updated: 2016/08/10 17:01:22 by smamba           ###   ########.fr       */
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
	t_vec3f	nhit;
	t_vec3f	pr;

	pr = vector_dir_multiply(*phit, tmat);
	nhit = sub_vec3f(&pr, pos);
	nhit.y = 0;
	return (normal_vec3f(&nhit));
}

t_vec3f	plane_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 tmat)
{
	t_vec3f	nhit;

	(void)phit;
	(void)tmat;
	nhit = dup_vec3f(pos);
	nhit.z = nhit.z < 0 ? -1 : (nhit.z > 0 ? 1 : 0);
	nhit.x = nhit.x < 0 ? -1 : (nhit.x > 0 ? 1 : 0);
	nhit.y = nhit.y < 0 ? -1 : (nhit.y > 0 ? 1 : 0);
	return (nhit);
}
