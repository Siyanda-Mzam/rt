/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 16:18:56 by smamba            #+#    #+#             */
/*   Updated: 2016/08/12 18:28:41 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

int		main(void)
{
	t_interface	iapp;

	iapp = init_tracer();
	iapp.camera = new_camera(new_vec3f(0, 13, 10),
							new_vec3f(0, 9, -1),
							new_vec3f(0, 1, 0), 30);
	iapp.camera.samples = 128;
	run_application(&iapp);
	return (0);
}
