/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 17:16:19 by smamba            #+#    #+#             */
/*   Updated: 2016/08/20 17:27:36 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

void	log_warning(const char *msg, ...)
{
	va_list args;

	va_start(args, msg);
	log_base(msg, "WARNING", args);
	va_end(args);
}

void	log_info(const char *msg, ...)
{
	va_list	args;

	va_start(args, msg);
	log_base(msg, "INFO", args);
	va_end(args);
}

void	log_error(const char *msg, ...)
{
	va_list	args;

	va_start(args, msg);
	log_base(msg, "ERROR", args);
	va_end(args);
}

void	log_critical(const char *msg, ...)
{
	va_list	args;

	va_start(args, msg);
	log_base(msg, "CRITICAL", args);
	va_end(args);
}
