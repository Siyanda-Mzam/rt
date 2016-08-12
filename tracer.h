/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 15:14:28 by smamba            #+#    #+#             */
/*   Updated: 2016/08/12 17:12:42 by smamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACER_H
# define TRACER_H
# define TRUE 1
# define FALSE 0
# include <matrix.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include "keys.h"
# define WIDTH 1200
# define HEIGHT 900
# define ARATIO WIDTH / (float)HEIGHT
# define FOV 30
# define BIAS 1e-4

enum			e_objects
{
	SPHERE = 1,
	CONE,
	CYLINDER,
	PLANE,
	BOX,
	LIGHT,
	POINT_LIGHT,
	AREA_LIGHT
};

typedef struct	s_gui
{
	void	*mlx;
	void	*win;
	char	*title;
	int		width;
	int		height;
	int		bpp;
	int		endian;
	int		sl;
	void	*image;
	char	*pixel;
}				t_gui;

typedef t_vec3f	t_color;

typedef struct	s_ray
{
	t_vec3f	origin;
	t_vec3f	dir;
}				t_ray;

typedef struct	s_object
{
	t_mat44		o_matrix;
	t_mat44		inverse_matrix;
	t_vec3f		(*normal)(t_vec3f*, t_vec3f*, t_mat44);
	t_vec3f		plane_normal;
	t_vec3f		pos;
	t_vec3f		size;
	t_vec3f		orientation;
	t_color		scolor;
	t_color		ecolor;
	t_bool		reflection;
	t_bool		mirror;
	t_bool		(*intersect)(t_ray*, struct s_object*, t_f64*, t_f64*);
	t_f64		transparency;
	t_f64		radius;
	int			type;
	int			nature;
}				t_object;

typedef struct	s_objects
{
	int			top;
	t_object	*store;
	int			size;
}				t_objects;

typedef t_objects	t_stack;

typedef struct	s_camera
{
	t_vec3f		pos;
	t_vec3f		target;
	t_vec3f		up;
	t_f64		fov;
	t_f64		angle;
	t_matrix	view;
	t_i32		samples;
}				t_camera;

typedef struct	s_params
{
	t_ray		*ray;
	t_vec3f		nhit;
	t_vec3f		phit;
	int			depth;
	double		tnear;
	t_object	*sphere;
}				t_params;

typedef struct  s_interface
{
	t_stack		*objects;
	t_camera	camera;
	t_gui		gui;
}				t_interface;

double			mix(const t_f64 a, const t_f64 b, const t_f64 mix);
double			ft_min(const t_f64 a, const t_f64 b);
double			ft_max(const t_f64 a, const t_f64 b);
t_gui			new_gui(int w, int h, char *title);
t_objects		*new_stack(int size);
t_objects		*push_object(t_objects *sps, t_object *s);
t_objects		*scene_one();
t_object		get_object(t_objects *s, int idx);
t_object		new_cylinder(t_vec3f p, t_color s, t_color e, t_f64 f, t_f64 r);
t_object		new_light(t_vec3f p, t_color s, t_f64 rf);
t_object		new_plane(t_vec3f p, t_color s, t_color e, t_f64 ref);
void			kill_stack(t_objects **sp);
t_color			new_color(double r, double g, double b);
t_color			new_uni_color(double a);
t_ray			dup_ray(t_ray *r);
t_ray			new_ray(t_vec3f origin, t_vec3f dir);
t_ray			*new_hray(t_vec3f o, t_vec3f dir);
t_object		new_sphere(t_vec3f pos, t_color s, t_color e,
		t_f64 rd, t_f64 r);
t_vec3f			trace_ray(t_ray *ray, t_objects *sp, int depth);
t_bool			sphere_intersection(t_ray *r, t_object *s, t_f64 *t, t_f64 *a);
t_bool			intersect_ray(t_ray *r, t_object *s);
t_vec3f			trace_ray_2(t_ray *ray, t_objects *sp, double depth);
t_bool			solve_quadratic(t_f64 a, t_f64 b, t_f64 c, t_f64 *u, t_f64 *v);
t_bool			cylinder_intersection(t_ray *r, t_object *s,
		t_f64 *u, t_f64 *v);
t_bool			plane_intersection(t_ray *r, t_object *s, t_f64 *t0, t_f64 *t1);
t_camera		new_camera(t_vec3f eye, t_vec3f target, t_vec3f up, t_f64 fov);
t_vec3f			sphere_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 t);
t_vec3f			cylinder_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 t);
t_vec3f			plane_normal(t_vec3f *phit, t_vec3f *pos, t_mat44 t);
void			paint_mlx(t_vec3f *a, t_gui gui);
int				expose_handler(t_interface *env);
void			render_scene(t_interface *env);
void			run_application(t_interface *env);
int				onkey_handler(int key, t_interface *env);
t_interface		init_tracer();
void			kill_camera(t_camera *m);
t_ray			transform_ray(t_ray *ray, t_mat44 mat);
#endif
