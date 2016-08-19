/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imod.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:40:43 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 15:41:19 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMOD_H
# define IMOD_H
# include "libft.h"
# include "ezxml.h"
# include "tracer.h"

t_object	make_object(t_object *obj, const char *name);
t_stack		*get_objects(ezxml_t xml);
t_camera	get_camera(ezxml_t xml);
t_vec3f		ato_vec3f(const char *str);
t_f64		*process_vector(const char *f);
const char	*ezxml_child_value(ezxml_t node, const char *name);
const char	*ezxml_child_soft(ezxml_t node, const char *name);
const char	*ezxml_attr_value(ezxml_t xml, const char *attr);
const char	*ezxml_attr_soft(ezxml_t xml, const char *attr);
ezxml_t		parse_scene_file(const char *file);
t_bool		ft_isnum(const char *f);
#endif
