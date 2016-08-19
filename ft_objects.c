/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 16:37:19 by smamba            #+#    #+#             */
/*   Updated: 2016/08/17 16:42:30 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_object	new_object(t_vec3f pos, t_vec3f o, int t)
{
	t_object	sp;

	sp.pos = pos;
	sp.orientation = o;
	if (t == CYLINDER || t == CONE)
		sp.inverse_matrix = inverse_mat44(new_orientation_mat44(o));
	sp.ecolor = new_uni_color(0);
	sp.radius = 0;
	sp.transparency = 0;
	sp.reflection = FALSE;
	sp.type = -1;
	sp.mirror = FALSE;
	return (sp);
}

t_object	new_sphere(t_vec3f pos, t_vec3f o, t_color s, t_f64 rad)
{
	t_object	sp;

	sp = new_object(pos, o, SPHERE);
	sp.radius = rad;
	sp.scolor = s;
	sp.intersect = sphere_intersection;
	sp.normal = sphere_normal;
	return (sp);
}

t_object	new_cone(t_vec3f pos, t_vec3f o, t_color s, t_f64 rad)
{
	t_object	cone;

	cone = new_object(pos, o, CONE);
	cone.radius = rad;
	cone.scolor = s;
	cone.alpha = rad;
	cone.intersect = cone_intersection;
	cone.normal = cone_normal;
	return (cone);
}

t_object	new_plane(t_vec3f pos, t_vec3f size, t_color s)
{
	t_object	plane;

	plane = new_object(pos, size, PLANE);
	plane.size = size;
	plane.scolor = s;
	plane.intersect = plane_intersection;
	plane.normal = plane_normal;
	return (plane);
}

t_object	new_cylinder(t_vec3f pos, t_vec3f o, t_color s, t_f64 rad)
{
	t_object	sp;

	sp = new_object(pos, o, CYLINDER);
	sp.radius = rad;
	sp.scolor = s;
	sp.intersect = cylinder_intersection;
	sp.normal = cylinder_normal;
	return (sp);
}

t_object	new_light(t_vec3f pos, t_color s, t_f64 rad)
{
	t_object	light;

	light = new_sphere(pos, new_uni_color(0), s, rad);
	light.type = LIGHT;
	light.nature = POINT_LIGHT;
	light.ecolor = s;
	return (light);
}
