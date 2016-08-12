/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 16:10:10 by smamba            #+#    #+#             */
/*   Updated: 2016/07/21 12:55:45 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_ray	new_ray(t_vec3f origin, t_vec3f dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	return (ray);
}

t_ray	dup_ray(t_ray *src)
{
	t_ray	dest;

	dest.origin = src->origin;
	dest.dir = src->dir;
	return (dest);
}

t_ray	*new_hray(t_vec3f origin, t_vec3f dir)
{
	t_ray	*ray;

	ray = (t_ray*)malloc(sizeof(t_ray));
	ray->origin = origin;
	ray->dir = dir;
	return (ray);
}

t_ray	transform_ray(t_ray *ray, t_mat44 mat)
{
	t_ray	tray;

	tray.origin = vector_multiply(ray->origin, mat);
	tray.dir = normalize_vec3f(vector_dir_multiply(ray->dir, mat));
	return (tray);
}
