/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 18:16:02 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 18:52:27 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

int		g_soffset = 0;
int		g_fds[10];

void	print_tag(const char *tag)
{
	ft_putstr("   [");
	ft_putstr(tag);
	ft_putstr("]   ");
}

void	log_base(const char *msg, const char *tag, ...)
{
	char	*tim;
	va_list	valist;
	time_t	now;

	time(&now);
	va_start(valist, tag);
	tim = ctime(&now);
	tim[ft_strlen(tim) - 1] = 0;
	ft_putstr(tim);
	print_tag(tag);
	while (*msg)
	{
		if (*msg == '%' && *(msg + 1) == 's')
		{
			msg++;
			ft_putstr((char*)va_arg(valist, char*));
		}
		else
			ft_putchar(*msg);
		msg++;
	}
	ft_putchar('\n');
}

void	log_set_output_device(const int fd)
{
	if (g_soffset == 0 && fd > 0)
		g_fds[g_soffset++] = fd;
}
