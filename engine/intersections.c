/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 16:21:06 by smamba            #+#    #+#             */
/*   Updated: 2016/07/31 15:40:23 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"
#include <math.h>

t_bool	plane_intersection(t_ray *r, t_object *s, t_f64 *t0, t_f64 *t1)
{
	t_f64	denom;
	t_vec3f	v_n;
	t_vec3f	c;
	t_vec3f	f;

	v_n = s->pos;
	denom = dot_vec3f(&v_n, &r->dir);
	if (denom > 1e-6)
	{
		f = sub_vec3f(&s->pos, &r->origin);
		*t0 = dot_vec3f(&f, &v_n) / denom;
		*t1 = *t0;
		c = scale_vec3f(&r->dir, *t0);
		c = add_vec3f(&c, &r->origin);
		
		if (s->pos.y == 0)
		{
			if (!((c.y > -4) && (c.y < (s->pos.y + s->size.y))))
				return (FALSE);
		}
		return (*t0 >= 0);
	}
	return (FALSE);
}

t_bool	cylinder_intersection(t_ray *r, t_object *s, t_f64 *t0, t_f64 *t1)
{
	t_ray	tray;
	t_vec3f	diff;
	t_vec3f	dir;
	t_f64	b;
	t_f64	c;

	tray = transform_ray(r, s->inverse_matrix);
	dir = tray.dir;
	diff = sub_vec3f(&tray.origin, &s->pos);
	diff.y = 0;
	dir.y = 0;
	b = 2 * (dot_vec3f(&diff, &dir));
	c = dot_vec3f(&diff, &diff) - pow(s->radius, 2);
	if (!solve_quadratic(dot_vec3f(&dir, &dir), b, c, t0, t1))
		return (FALSE);
	return (TRUE);
}

t_bool	sphere_intersection(t_ray *r, t_object *s, t_f64 *t0, t_f64 *t1)
{
	t_vec3f	diff;
	float	tca;
	float	thc;
	float	d2;

	diff = sub_vec3f(&s->pos, &r->origin);
	tca = dot_vec3f(&diff, &r->dir);
	if (tca < 0)
		return (FALSE);
	d2 = dot_vec3f(&diff, &diff) - tca * tca;
	if (d2 > (s->radius * s->radius))
		return (FALSE);
	thc = sqrt(s->radius * s->radius - d2);
	*t0 = tca - thc;
	*t1 = tca + thc;
	return (TRUE);
}

t_bool	cone_intersection(t_ray *r, t_object *s, t_f64 *t0, t_f64 *t1)
{
	t_ray	t;
	t_vec3f	diff;
	t_f64	a;
	t_f64	b;
	t_f64	c;

	t = transform_ray(r, s->inverse_matrix);
	diff = sub_vec3f(&t.origin, &s->pos);
	a = pow(cos(s->alpha), 2) * (pow(t.dir.x, 2) + pow(t.dir.z, 2)) -
		pow(sin(s->alpha), 2) * pow(t.dir.y, 2);
	b = 2 * pow(cos(s->alpha), 2) * ((diff.x * t.dir.x) + (diff.z * t.dir.z))
		- 2 * pow(sin(s->alpha), 2) * pow(t.dir.y, 2);
	c = pow(cos(s->alpha), 2) * (pow(diff.x, 2) + pow(diff.z, 2))
		- pow(sin(s->alpha), 2) * pow(diff.y, 2);
	if (!solve_quadratic(a, b, c, t0, t1))
		return (FALSE);
	return (TRUE);
}
