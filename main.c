/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 16:18:56 by smamba            #+#    #+#             */
/*   Updated: 2016/08/18 18:02:43 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"
#include "imod/imod.h"

ezxml_t	open_scene(const char *file)
{
	ezxml_t	node;
	t_i32	fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit(0, ANSI_RED "IOError: Could not open file" ANSI_RED);
	else
		close(fd);
	return (parse_scene_file(file));
}

void	display_scene(int argc, char *argv)
{
	ezxml_t		root;
	t_interface	iapp;

	if (argc != 2)
		ft_exit(0, "Usage: ./RT scenefile");
	root = open_scene(argv);
	iapp = init_tracer();
	iapp.camera = get_camera(root);
	iapp.objects = get_objects(root);
	run_application(&iapp);
}

int		main(int ac, char *argv[])
{
	display_scene(ac, argv[1]);
	return (0);
}
