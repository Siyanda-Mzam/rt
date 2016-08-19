/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 16:23:14 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:10:43 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imod.h"

t_object	make_object(t_object *obj, const char *name)
{
	t_object	prop;

	if (!ft_strcmp(name, "cylinder"))
		prop = new_cylinder(obj->pos, obj->orientation,
							obj->scolor, obj->radius);
	else if (!ft_strcmp(name, "cone"))
		prop = new_cone(obj->pos, obj->orientation, obj->scolor, obj->alpha);
	else if (!ft_strcmp(name, "sphere"))
		prop = new_sphere(obj->pos, obj->orientation, obj->scolor, obj->radius);
	else if (!ft_strcmp(name, "plane"))
		prop = new_plane(obj->pos, obj->size, obj->scolor);
	else if (!ft_strcmp(name, "light"))
		prop = new_light(obj->pos, obj->ecolor, obj->radius);
	prop.reflection = obj->reflection;
	prop.transparency = obj->transparency;
	return (prop);
}
