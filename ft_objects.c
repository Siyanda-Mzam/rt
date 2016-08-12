/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 16:37:19 by smamba            #+#    #+#             */
/*   Updated: 2016/08/12 17:27:13 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_object	new_object(t_vec3f pos, t_vec3f o, t_color s, t_f64 r, int t)
{
	t_object	sp;

	sp.pos.x = pos.x;
	sp.pos.y = pos.y;
	sp.pos.z = pos.z;
	sp.scolor = s;
	sp.orientation = o;
	sp.o_matrix = new_orientation_mat44(o);
	sp.inverse_matrix = inverse_mat44(sp.o_matrix);
	sp.ecolor = new_uni_color(0);
	sp.radius = 0;
	sp.transparency = 0;
	sp.reflection = r;
	sp.type = t;
	sp.mirror = FALSE;
	return (sp);
}

t_object	new_sphere(t_vec3f pos, t_vec3f o, t_color s, t_f64 rad, t_f64 r)
{
	t_object	sp;

	sp = new_object(pos, o, s, r, SPHERE);
	sp.radius = rad;
	sp.intersect = sphere_intersection;
	sp.normal = sphere_normal;
	return (sp);
}

t_object	new_plane(t_vec3f pos, t_vec3f size, t_color s, t_f64 ref)
{
	t_object	plane;

	plane = new_object(pos, size, s, ref, PLANE);
	plane.size = size;
	plane.intersect = plane_intersection;
	plane.normal = plane_normal;
	return (plane);
}

t_object	new_cylinder(t_vec3f pos, t_vec3f o, t_color s, t_f64 rad, t_f64 r)
{
	t_object	sp;

	sp = new_object(pos, o, s, r, CYLINDER);
	sp.radius = rad;
	sp.intersect = cylinder_intersection;
	sp.normal = cylinder_normal;
	return (sp);
}

t_object	new_light(t_vec3f pos, t_color s, t_f64 rad)
{
	t_object	light;

	light = new_sphere(pos, new_uni_color(0), s, rad, 0);
	light.type = LIGHT;
	light.nature = AREA_LIGHT;
	light.ecolor = s;
	return (light);
}
