/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:46:49 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:46:50 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imod.h"

t_vec3f	ato_vec3f(const char *file)
{
	t_vec3f	pos;
	t_f64	*rpos;

	if (file == NULL)
		ft_exit(0, "IOError: Invalid value in scene file");
	rpos = process_vector(file);
	free(rpos);
	if (rpos == NULL)
		ft_exit(0, "InternalError: Variable referenced to NULL");
	pos.x = rpos[0];
	pos.y = rpos[1];
	pos.z = rpos[2];
	return (pos);
}
