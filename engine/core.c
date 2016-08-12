/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 15:35:59 by smamba            #+#    #+#             */
/*   Updated: 2016/08/07 13:43:21 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static inline	t_color	recursive_tracer(t_params p, t_ray *ray, t_objects *sp)
{
	t_f64	inside;
	t_f64	facingratio;
	t_f64	fresneleffect;
	t_vec3f	refldir;
	t_vec3f	refdir;
	t_color	reflection;
	t_color	refrac;
	t_ray	rx;

	if ((inside = dot_vec3f(&ray->dir, &p.nhit) > 0))
		p.nhit = scale_vec3f(&p.nhit, -1);
	facingratio = -dot_vec3f(&ray->dir, &p.nhit);
	fresneleffect = mix(pow(1 - facingratio, 3), 1, .1);
	refldir = get_reflection_dir(&p.nhit, &ray->dir);
	rx = reflected_ray(ray, &refldir, &p.nhit, &p.phit);
	reflection = trace_ray(&rx, sp, ++p.depth);
	if (p.sphere->mirror == TRUE)
	{
		refrac = trace_ray(&rx, sp, ++p.depth);
		p.sphere->transparency = .5;
	}
	else if (p.sphere->transparency > 0)
	{
		refdir = compute_ideal_refractions(ray, inside, p);
		rx = refracted_ray(ray, &refdir, &p.nhit, &p.phit);
		refrac = trace_ray(&rx, sp, ++p.depth);
	}
	return (defualt_glossy_shading(&reflection,
				&refrac, fresneleffect, p.sphere));
}

static inline t_color	sharp_shadows(t_params p,
				t_ray *r, t_objects *s, t_vec3f ld)
{
	t_f64	t0;
	int		i;
	t_ray	sray;

	i = 0;
	while (i < s->top)
	{
		if (s->store[i].type != LIGHT)
		{
			sray = dup_ray(r);
			sray.origin = scale_vec3f(&p.nhit, BIAS);
			sray.origin = add_vec3f(&sray.origin, &p.phit);
			sray.dir = ld;
			if (s->store[i].intersect(&sray, &s->store[i], &t0, &t0))
				return (new_uni_color(0));
		}
		i++;
	}
	return (new_uni_color(1));
}

static inline t_color	soft_shadows(t_params p, t_ray *r, t_objects *s, int j)
{
	int		x;
	int		y;
	t_color	trans;
	t_vec3f	tmp;
	t_vec3f	lp;

	trans = new_uni_color((x = 0));
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			tmp = new_vec3f(x, 0, y);
			lp = add_vec3f(&s->store[j].pos, &tmp);
			if (sharp_shadows(p, r, s,
				normalize_vec3f(sub_vec3f(&lp, &p.phit))).x != 0)
			{
				t_vec3f w = new_vec3f(1 / 9. , 1 / 9. , 1 / 9.);
				trans = add_vec3f(&trans, &w);
			}
			y++;
		}
		x++;
	}
	return (trans);
}

t_vec3f	single_tracer(t_params p, t_ray *ray, t_objects *sp)
{
	int		i;
	t_vec3f	trans;
	t_vec3f	tmp;
	t_vec3f	light_dir;
	t_color	scolor;

	i = 0;
	if (dot_vec3f(&ray->dir, &p.nhit) > 0)
		p.nhit = scale_vec3f(&p.nhit, -1);
	scolor = new_uni_color(0);
	while (i < sp->top)
	{
		if (sp->store[i].type == LIGHT)
		{
			light_dir = normalize_vec3f(sub_vec3f(&sp->store[i].pos, &p.phit));
			if (sp->store[i].nature == AREA_LIGHT)
				trans = soft_shadows(p, ray, sp, i);
			else
				trans = sharp_shadows(p, ray, sp, light_dir);
			tmp = phong_shading(trans, ray, p, light_dir, sp->store[i].ecolor);
			scolor = add_vec3f(&scolor, &tmp);
		}
		i++;
	}
	return (add_vec3f(&scolor, &p.sphere->ecolor));
}

t_vec3f	trace_ray(t_ray *ray, t_objects *sp, int depth)
{
	t_params	param;

	param = get_closest_primitive(ray, sp);
	param.depth = depth;
	if (param.sphere == NULL)
		return (new_uni_color(3));
	param.phit = scale_vec3f(&ray->dir, param.tnear);
	param.phit = add_vec3f(&ray->origin, &param.phit);
	param.nhit = param.sphere->normal(&param.phit, &param.sphere->pos,
			param.sphere->inverse_matrix);
	param.ray = ray;
	if ((param.sphere)->reflection > 0 && depth < MAX_RAY_DEPTH)
		return (recursive_tracer(param, ray, sp));
	return (single_tracer(param, ray, sp));
}
