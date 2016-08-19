/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:33:00 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:36:03 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imod.h"

t_bool	ft_isnum(const char *f)
{
	if (f == NULL)
		return (FALSE);
	while (*f)
	{
		if (!ft_isdigit(*f) &&
			(*f != ' ' && *f != '.' && *f != '\t' && *f == '-' && *f == '+'))
			return (FALSE);
		f++;
	}
	return (TRUE);
}

t_f64	*process_vector(const char *f)
{
	int		i;
	int		size;
	char	**sp;
	t_f64	*vec;

	i = 0;
	size = 0;
	vec = NULL;
	sp = ft_strsplit(f, ',');
	while (sp[size])
	{
		if (!ft_isnum(sp[size++]))
			ft_exit(0, "IOError: Invalid value found in scene file");
	}
	vec = (t_f64*)malloc(sizeof(t_f64) * size);
	if (vec == NULL)
		ft_exit(0, "MemoryError: Out of memory");
	while (sp[i])
	{
		vec[i] = ft_atodouble(sp[i]);
		free(sp[i]);
		i++;
	}
	free(sp);
	return (vec);
}
