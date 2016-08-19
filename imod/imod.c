/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:11:10 by smamba            #+#    #+#             */
/*   Updated: 2016/08/19 18:00:50 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imod.h"

ezxml_t		parse_scene_file(const char *file)
{
	static ezxml_t	xml = NULL;

	if (xml == NULL)
		xml = ezxml_parse_file(file);
	if (xml == NULL)
		ft_exit(0, "IOError: Could not open scene file");
	return (xml);
}

void		extended_attributes(t_object *obj, ezxml_t xml, char *name)
{
	if (!ft_strcmp(name, "light"))
	{
		if (!ft_strcmp(ezxml_attr_soft(xml, "type"), "AREA_LIGHT"))
			obj->nature = AREA_LIGHT;
		else if (!ft_strcmp(ezxml_attr_soft(xml, "type"), "POINT_LIGHT"))
			obj->nature = POINT_LIGHT;
		else
			ft_putstr("IOWarning: Unkown light type ");
		obj->ecolor = scale_vec3f(&obj->ecolor,
			ft_atodouble(ezxml_child_value(xml, "intensity")));
		ft_atodouble(ezxml_child_value(xml, "intensity"));
	}
	if (ft_strcmp(name, "light"))
	{
		obj->transparency = ft_atodouble(ezxml_child_soft(xml, "transparency"));
		obj->reflection = ft_atoi(ezxml_child_soft(xml, "reflection"));
	}
	if (!ft_strcmp(name, "cone"))
		obj->alpha = ft_atodouble(ezxml_child_value(xml, "alpha"));
}

void		add_objects(t_stack *stk, ezxml_t tree, char *name)
{
	t_object	obj;
	t_color		color;
	ezxml_t		node;

	if ((node = ezxml_child(tree, name)) == NULL)
		return ;
	while (node)
	{
		obj.pos = ato_vec3f(ezxml_child_value(node, "pos"));
		if (!ft_strcmp(name, "plane"))
			obj.size = ato_vec3f(ezxml_child_value(node, "size"));
		if (!ft_strcmp(name, "sphere") || !ft_strcmp(name, "cylinder"))
			obj.radius = ft_atodouble(ezxml_child_value(node, "radius"));
		if (!ft_strcmp(name, "cone") || !ft_strcmp(name, "cylinder"))
			obj.orientation = ato_vec3f(ezxml_child_value(node, "orientation"));
		color = (t_color)ato_vec3f(ezxml_child_value(node, "color"));
		if (!ft_strcmp(name, "light"))
			obj.ecolor = color;
		else
			obj.scolor = color;
		obj = make_object(&obj, name);
		extended_attributes(&obj, node, name);
		push_object(stk, &obj);
		node = node->next;
	}
}

t_stack		*get_objects(ezxml_t xml)
{
	t_stack	*stack;

	stack = new_stack(20);
	add_objects(stack, xml, "sphere");
	add_objects(stack, xml, "cone");
	add_objects(stack, xml, "plane");
	add_objects(stack, xml, "cylinder");
	add_objects(stack, xml, "light");
	return (stack);
}

t_camera	get_camera(ezxml_t tree)
{
	int			samples;
	t_camera	cam;
	ezxml_t		node;
	const char	*type;

	node = ezxml_child(tree, "camera");
	if (node == NULL)
		ft_exit(0, "IOError: Could not find camera tag in scene file");
	type = ezxml_attr_value(node, "type");
	if (!ft_strcmp(type, "LookAt"))
		cam.type = LOOKAT;
	else
		ft_exit(0, "IOError: Unkown camera type");
	cam.pos = ato_vec3f(ezxml_child_value(node, "pos"));
	cam.target = ato_vec3f(ezxml_child_value(node, "lookat"));
	cam.fov = ft_atodouble(ezxml_child_value(node, "fov"));
	samples = ft_atoi(ezxml_child_value(node, "samples"));
	cam.up = ato_vec3f(ezxml_child_value(node, "up"));
	cam = new_camera(cam.pos, cam.target, cam.up, cam.fov);
	cam.samples = samples;
	return (cam);
}
