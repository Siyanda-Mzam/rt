/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoong <mchoong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:12:37 by mchoong           #+#    #+#             */
/*   Updated: 2013/11/22 19:13:06 by mchoong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *s1, const char *s2)
{
	char	*temp_s1;

	temp_s1 = s1;
	while (*s2 != '\0')
		*s1++ = *s2++;
	*s1 = '\0';
	return (temp_s1);
}