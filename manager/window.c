/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 13:58:05 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 16:17:08 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"

t_gui	new_gui(int w, int h, char *title)
{
	t_gui	gui;

	if ((gui.mlx = mlx_init()) == NULL)
		ft_exit(0, "FetalError: mlx could not initialize");
	gui.win = mlx_new_window(gui.mlx, w, h, title);
	gui.width = w;
	gui.height = h;
	gui.title = title;
	gui.image = mlx_new_image(gui.mlx, w, h);
	gui.pixel = mlx_get_data_addr(gui.image, &gui.bpp, &gui.sl, &gui.endian);
	return (gui);
}

void	paint_mlx(t_vec3f *a, t_gui gui)
{
	int				x;
	int				y;
	int				pos;
	static t_bool	rendered = FALSE;

	x = 0;
	y = 0;
	if (rendered)
		return (void)mlx_put_image_to_window(gui.mlx, gui.win, gui.image, 0, 0);
	while (y < HEIGHT && !(x = 0))
	{
		while (x < WIDTH)
		{
			pos = (x * gui.bpp / 8) + (y * gui.sl);
			gui.pixel[pos] = (unsigned char)(ft_min(1.0, (*a).z) * 255);
			gui.pixel[pos + 1] = (unsigned char)(ft_min(1.0, (*a).y) * 255);
			gui.pixel[pos + 2] = (unsigned char)(ft_min(1.0, (*a).x) * 255);
			a++;
			x++;
		}
		y++;
	}
	rendered = TRUE;
	dispose_garbage();
	mlx_put_image_to_window(gui.mlx, gui.win, gui.image, 0, 0);
}

int		expose_handler(t_interface *env)
{
	render_scene(env);
	mlx_string_put(env->gui.mlx, env->gui.win, 10, 15, 0xff0000, "Rat Tracing");
	return (0);
}

int		onkey_handler(int key, t_interface *env)
{
	if (key == ESC)
	{
		//mlx_destroy_image(env->gui.mlx, env->gui.image);
		mlx_destroy_window(env->gui.mlx, env->gui.win);
		ft_exit(0, ANSI_GREEN"Info: Now exiting the program"ANSI_GREEN);
	}
	return (key);
}
