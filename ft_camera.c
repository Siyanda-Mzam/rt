/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:38:48 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 16:20:27 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_mat44	new_lookat_matrix(t_vec3f eye, t_vec3f target, t_vec3f up)
{
	t_vec3f	n;
	t_vec3f	u;
	t_vec3f	v;
	t_vec3f	e;
	t_mat44	view;

	view = new_mat44(4);
	n = normalize_vec3f(sub_vec3f(&eye, &target));
	u = normalize_vec3f(cross_vec3f(&up, &n));
	v = cross_vec3f(&n, &u);	
	e.x = dot_vec3f(&u, &eye);
	e.y = dot_vec3f(&v, &eye);
	e.z = dot_vec3f(&n, &eye);
	set_row(view, 0, (t_f64[4]){u.x, u.y, u.z, -e.x});
	set_row(view, 1, (t_f64[4]){v.x, v.y, v.z, -e.y});
	set_row(view, 2, (t_f64[4]){n.x, n.y, n.z, -e.z});
	set_row(view, 3, (t_f64[4]){0, 0, 0, 1});
	return (view);
}

t_mat44	new_fps_matrix(t_vec3f eye, float pitch, float yaw)
{
	float sin_yaw;
	float cos_yaw;
	float sin_pitch;
	float cos_pitch;
	t_vec3f xaxis;
	t_vec3f yaxis;
	t_vec3f zaxis;
	t_mat44	view;

	sin_yaw = sin(yaw);
	cos_yaw = cos(yaw);
	sin_pitch = sin(pitch);
	cos_pitch = cos(pitch);
	xaxis = (t_vec3f){cos_yaw, 0, -sin_yaw};
	yaxis = (t_vec3f){sin_yaw * cos_pitch, cos_pitch, cos_yaw * sin_pitch};
	zaxis = (t_vec3f){sin_yaw * cos_pitch, -sin_pitch, cos_pitch * cos_yaw};
	set_row(view, 0, (t_f64[4]){xaxis.x, yaxis.x, zaxis.x, 0});
	set_row(view, 1, (t_f64[4]){xaxis.y, yaxis.x, zaxis.x, 0});
	set_row(view, 2, (t_f64[4]){xaxis.z, yaxis.z, zaxis.z, 0});
	set_row(view, 3, (t_f64[4]){-dot_vec3f(&xaxis, &eye),
								-dot_vec3f(&yaxis, &eye), 
								-dot_vec3f(&zaxis, &eye), 1});
	return (view);
}

t_camera	new_camera(t_vec3f eye, t_vec3f target, t_vec3f up, t_f64 fov)
{
	t_camera	cam;

	cam.pos = eye;
	cam.target = target;
	cam.up = up;
	cam.fov = fov;
	cam.angle = tan(M_PI * 0.5 * fov / 180);
	cam.view = new_lookat_matrix(eye, target, up);
	cam.samples = 1;
	return (cam);
}

t_vec2f		maya_style(int x, int y, t_interface *env)
{
	t_vec2f	vals;

	vals.x = (2. * ( ((x + rand() / (t_f64)RAND_MAX * (env->camera.samples > 1))
				+ 0.5) / WIDTH) - 1) * env->camera.angle * ARATIO;
	vals.y = (1. - 2 * (((y + rand() / (t_f64)RAND_MAX *
				(env->camera.samples > 1)) + 0.5) / HEIGHT))
				* env->camera.angle;
	return (vals);
}

t_vec2f		default_style(int x, int y, t_interface *env)
{
	t_vec2f	vals;

	vals.x = (2. * ( ((x + rand() / (t_f64)RAND_MAX * (env->camera.samples > 1))
				+ 0.5) / WIDTH) - 1) * ARATIO;
	vals.y = (1. - 2 * (((y + rand() / (t_f64)RAND_MAX *
				(env->camera.samples > 1)) + 0.5) / HEIGHT));
	return (vals);
}

void		kill_camera(t_camera *cam)
{
	kill_matrix(&(cam->view));
}
