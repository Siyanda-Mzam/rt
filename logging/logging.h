/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 18:05:43 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 18:19:10 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H
# include <tracer.h>
# include <time.h>

void	log_set_output_device(const int fd);
void	log_set_log_path(const char *path);
void	log_base(const char *msg, ...);
void	log_warning(const char *msg, ...);
void	log_error(const char *msg, ...);
void	log_info(const char *msg, ...);
int		log_get_output_device();
#endif
