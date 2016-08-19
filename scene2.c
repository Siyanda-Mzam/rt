/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/31 14:30:48 by smamba            #+#    #+#             */
/*   Updated: 2016/08/17 16:40:07 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_objects	*scene_one()
{
	t_stack   *vector = new_stack(11);

	t_object    sp2 = new_sphere(new_vec3f(-6, 0, -15),
                                 new_vec3f(0., 0., 0.),
                                 new_color(1.00, .32, .36),
                                 2);

	t_object	sp3 = new_cylinder(new_vec3f(9, -1, -28),
								 new_vec3f(0, 0.0, -2.1),
								 new_color(0.90, 0.76, 0.46),
								 2);
	
	t_object	sp6 = new_plane(new_vec3f(0, -2, 0),
								 new_vec3f(0.0, 0.0, 0.0),
								 new_color(.75, .75, .75));
	
	t_object	cyl =  new_plane(new_vec3f(0, 0, -30),
								 new_vec3f(0.0, 20.0, 0.0),
								 new_color(.3, .3, .4 + .1));
	
	t_object    lig = new_light(new_vec3f(16, 20, 40),
                                new_color(3, 3, 3), 1);

	t_object    lig2 = new_light(new_vec3f(-16, 20, 40),
                                new_color(3, 3, 3), 1);
                                
	t_object	sp0 = new_sphere(new_vec3f(5, 0, -12),
								 new_vec3f(0.0, 0.0, 0.0),
								 new_color(0.95, 0.47, 0.77),
								 1.5);

	t_object	cone = new_cone(new_vec3f(-5, 0, -28),
								new_vec3f(0, 0, 2.5),
								new_color(.7, .7, .4),
								M_PI / 9.);
	push_object(vector, &sp2);
	push_object(vector, &sp3);
	push_object(vector, &sp6);
	push_object(vector, &lig);
	push_object(vector, &sp0);
	push_object(vector, &lig2);
	push_object(vector, &cyl);
	push_object(vector, &cone);
	return (vector);
}
