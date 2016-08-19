/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 16:44:28 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 16:14:17 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_interface	init_tracer(void)
{
	t_interface	i;

	i.gui = new_gui(WIDTH, HEIGHT, "Ray Tracing");
	return (i);
}

void		cast_ray(int x, int y, t_vec3f *pixel, t_interface *env)
{
	t_vec3f	dir;
	t_vec2f	proj;
	t_ray	ray;
	t_i32	j;

	j = 0;
	while (j < env->camera.samples)
	{
		proj = maya_style(x, y, env);
		dir = vector_dir_multiply(new_vec3f(proj.x, proj.y, -1),
									env->camera.view);
		ray = new_ray(env->camera.pos, normalize_vec3f(dir));
		if (j == 0)
			*pixel = trace_ray(&ray, env->objects, 0);
		else
		{
			dir = trace_ray(&ray, env->objects, 0);
			*pixel = add_vec3f(pixel, &dir);
		}
		j++;
	}
	*pixel = scale_vec3f(pixel, 1. / (t_f64)env->camera.samples);
}

void		render_scene(t_interface *env)
{
	int				x;
	int				y;
	t_vec3f			*image;
	static t_bool	rendered = FALSE;
	t_vec3f			*pixel;

	if (rendered == TRUE)
		return (void)paint_mlx(NULL, env->gui);
	image = (t_vec3f*)malloc(sizeof(t_vec3f) * (WIDTH * HEIGHT));
	y = 0;
	pixel = image;
	while (y < HEIGHT && !(x = 0))
	{
		while (x < WIDTH)
		{
			cast_ray(x, y, pixel++, env);
			x++;
		}
		y++;
	}
	rendered = TRUE;
	paint_mlx(image, env->gui);
	kill_stack(&env->objects);
	free(image);
}

void		run_application(t_interface *env)
{
	if (env->objects->top == 0)
		ft_exit(0, "InternalError: No objects in stack");
	mlx_key_hook(env->gui.win, onkey_handler, env);
	mlx_expose_hook(env->gui.win, expose_handler, env);
	mlx_loop(env->gui.mlx);
	kill_stack(&env->objects);
	dispose_garbage();
}
