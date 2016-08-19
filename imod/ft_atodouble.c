/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:42:06 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:45:32 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imod.h"

const char	*shift_ptr(const char *str)
{
	if (str == NULL)
		ft_exit(0, ANSI_RED"IOError: Invalid value in scene file"ANSI_RED);
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

t_f64		ft_atodouble(const char *str)
{
	t_f64	value;
	int		sign;
	int		i;

	value = 0;
	str = shift_ptr(str);
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '-' || *str == '+');
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str - '0');
		(str)++;
	}
	if (*str == '.')
	{
		(str)++;
		i = 1;
		while (ft_isdigit(*str))
		{
			value += (t_f64)(*str - '0') / pow(10, i++);
			(str)++;
		}
	}
	str += 2;
	return (value * sign);
}
