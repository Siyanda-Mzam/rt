* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/31 14:30:48 by smamba            #+#    #+#             */
/*   Updated: 2016/08/17 18:39:21 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_objects	*scene_one()
{
	t_stack   *vector = new_stack(10);

	t_object	sp1	= new_plane(new_vec3f(-8, 0, 0),
								 new_vec3f(0.0, 9, 0.0),
								 new_color(.5, .8, .5),
								 FALSE);
	t_object    sp2 = new_sphere(new_vec3f(0 -2, 0, -15),
                                 new_vec3f(0., 0., 0.),
                                 new_color(1.00, .32, .36),
                                 2, TRUE);
	t_object	sp3 = new_cylinder(new_vec3f(0, -1, -28),
								 new_vec3f(0, 0.0, 0),
								 new_color(0.90, 0.76, 0.46),
								 2, TRUE);
	t_object	sp4 = new_sphere(new_vec3f(2 , -.5, -15),
								 new_vec3f(0.0, 0.0, 0.0),
								 new_color(0.65, 0.77, 0.97),
								 1.5, TRUE);
	t_object	sp6 = new_plane(new_vec3f(0, -2, 0),
								 new_vec3f(0.0, 0.0, 0.0),
								 new_color(.75, .75, .75),
								FALSE);
	t_object	sp5 = new_sphere(new_vec3f(-3.5 - 2, -.5, -15 - 5),
								new_color(0.0, 0.0, 0.0),
								new_color(.9, .9, .9),
								1.5, TRUE);
	t_object	cyl =  new_plane(new_vec3f(0, 0, -30),
								 new_vec3f(0.0, 9.0, 0.0),
								 new_color(.3, .3, .5),
								 FALSE);
	t_object	l2 =  new_plane(new_vec3f(9, 0, 0),
								 new_vec3f(0.0, 9.0, 0.0),
								 new_color(.9, .3, .3),
								 FALSE);
	t_object    lig = new_light(new_vec3f(-1, 20, 4),
                                new_color(4, 4, 4), 1);
	t_object	sp0 = new_sphere(new_vec3f(5, 0, -7),
								 new_vec3f(0.0, 0.0, 0.0),
								 new_color(0.95, 0.47, 0.77),
								 1.5, FALSE);
	push_object(vector, &sp1);
	push_object(vector, &sp2);
	push_object(vector, &sp3);
	push_object(vector, &sp4);
	push_object(vector, &sp5);
	push_object(vector, &sp6);
	push_object(vector, &lig);
	push_object(vector, &sp0);
	push_object(vector, &cyl);
	push_object(vector, &l2);
	return (vector);
}
