/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:43:39 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:13:31 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

//  a · b = ax · bx + ay · by + az · bz

double	min_pos(double t1, double t2)
{
	if (t1 > 0 && t2 > 0)
		return (t1 < t2 ? t1 : t2);
	if (t1 > 0)
		return (t1);
	if (t2 > 0)
		return (t2);
	return (-1);
}

double	discriminant(double a, double b, double c)
{
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return ((-b - sqrt(discriminant)) / (2 * a));
}
// needs the solution of quadratic function
//  Camera
//   |
//   | ray
//   v
// O ----------- t1 ---- (sphere) ---- t2

static t_rgb	checker_planar(t_vec3 p)
{
	double	size;
	int		ix;
	int		iz;
	t_rgb	c;

	size = 10.0;
	ix = (int)floor(p.x / size);
	iz = (int)floor(p.z / size);
	if ((ix + iz) % 2 == 0)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
		return (c);
	}
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}

static t_rgb	checker_sphere(t_vec3 n)
{
	double	u;
	double	v;
	int		iu;
	int		iv;
	t_rgb	c;

	u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	iu = (int)floor(u * 8.0);
	iv = (int)floor(v * 8.0);
	if ((iu + iv) % 2 == 0)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
		return (c);
	}
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}

static void	cy_uv(t_vec3 p, t_cylinder *cy)
{
	cy->axis = vec3_norm(cy->vector);
	cy->proj_dir = vec3_sub(p, cy->center);
	cy->proj_oc = vec3_sub(cy->proj_dir, vec3_scale(cy->axis,
				vec3_dot(cy->proj_dir, cy->axis)));
	cy->h_check = (atan2(cy->proj_oc.z, cy->proj_oc.x) + M_PI) / (2.0 * M_PI);
	cy->disc = (vec3_dot(cy->proj_dir, cy->axis) / cy->height) + 0.5;
}

static t_rgb	checker_cylinder(t_vec3 p, t_cylinder *cy)
{
	int		iu;
	int		iv;
	t_rgb	c;

	cy_uv(p, cy);
	iu = (int)floor(cy->h_check * 10.0);
	iv = (int)floor(cy->disc * 10.0);
	if ((iu + iv) % 2 == 0)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
		return (c);
	}
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}

static void	co_uv(t_vec3 p, t_cone *co)
{
	co->axis = vec3_norm(co->axis);
	co->oc = vec3_sub(p, co->tip);
	co->dv = vec3_dot(co->oc, co->axis);
	co->oc = vec3_sub(co->oc, vec3_scale(co->axis, co->dv));
	co->h = (atan2(co->oc.z, co->oc.x) + M_PI) / (2.0 * M_PI);
	co->disc = co->dv / co->height;
}

static t_rgb	checker_cone(t_vec3 p, t_cone *co)
{
	int		iu;
	int		iv;
	t_rgb	c;

	co_uv(p, co);
	iu = (int)floor(co->h * 10.0);
	iv = (int)floor(co->disc * 10.0);
	if ((iu + iv) % 2 == 0)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
		return (c);
	}
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}

void	set_color(t_hit *result, t_object *obj, t_vec3 hit_point, t_vec3 normal)
{
	if (obj->checker)
	{
		if (obj->type == OBJ_SPHERE)
			result->color = checker_sphere(normal);
		else if (obj->type == OBJ_CYLINDER)
			result->color = checker_cylinder(hit_point, &obj->data.cylinder);
		else if (obj->type == OBJ_CONE)
			result->color = checker_cone(hit_point, &obj->data.cone);
		else
			result->color = checker_planar(hit_point);
		return ;
	}
	if (obj->type == OBJ_SPHERE)
		result->color = obj->data.sphere.color;
	else if (obj->type == OBJ_PLANE)
		result->color = obj->data.plane.color;
	else if (obj->type == OBJ_CYLINDER)
		result->color = obj->data.cylinder.color;
	else
		result->color = obj->data.cone.color;
}

double	get_dist(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (inter_sphere(ray, obj->data.sphere));
	if (obj->type == OBJ_PLANE)
		return (inter_plane(ray, obj->data.plane));
	if (obj->type == OBJ_CYLINDER)
		return (inter_cylinder(ray, obj->data.cylinder));
	if (obj->type == OBJ_CONE)
		return (inter_cone(ray, obj->data.cone));
	return (-1);
}

t_hit	closest_hit(t_ray ray, t_scene *scene)
{
	t_hit		result;
	t_object	*obj;
	double		dist;
	t_vec3		hit_point;

	result.hit = 0;
	result.t = -1;
	obj = scene->objects;
	while (obj)
	{
		dist = get_dist(ray, obj);
		if (dist > 0 && (!result.hit || dist < result.t))
		{
			result.t = dist;
			result.hit = 1;
			hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, dist));
			result.point = hit_point;
			set_normal(&result, obj, hit_point);
			set_color(&result, obj, hit_point, result.normal);
		}
		obj = obj->next;
	}
	return (result);
}

int	any_hit_before(t_ray ray, t_scene *scene, double max_t)
{
	t_object	*obj;
	double		dist;

	obj = scene->objects;
	while (obj)
	{
		dist = get_dist(ray, obj);
		if (dist > 1e-3 && dist < max_t)
			return (1);
		obj = obj->next;
	}
	return (0);
}

/*plane intersect is simpler than sphere, only needs linear solution
//denominator 0 means no hit, t < 0 plane is behind the ray
//            ray
//             \
//              \
//               \   t
//                \------X (intersection)
// ------------------------------*/

/*     intersections: side, top and bottom cap    */

static void	setup_cyl(t_ray ray, t_cylinder *cy)
{
	cy->axis = vec3_norm(cy->vector);
	cy->oc = vec3_sub(ray.origin, cy->center);
	cy->proj_dir = vec3_sub(ray.direction, vec3_scale(cy->axis,
				vec3_dot(ray.direction, cy->axis)));
	cy->proj_oc = vec3_sub(cy->oc, vec3_scale(cy->axis, vec3_dot(cy->oc,
					cy->axis)));
}

static double	disc_cyl(t_cylinder *cy)
{
	cy->a = vec3_dot(cy->proj_dir, cy->proj_dir);
	cy->b = 2.0 * vec3_dot(cy->proj_oc, cy->proj_dir);
	cy->c = vec3_dot(cy->proj_oc, cy->proj_oc) - (cy->radius * cy->radius);
	cy->disc = cy->b * cy->b - 4.0 * cy->a * cy->c;
	return (cy->disc);
}

static double	test_side(t_ray ray, t_cylinder *cy)
{
	double	t1;
	double	t2;
	double	ts;
	double	sqrt_d;

	ts = -1;
	sqrt_d = sqrt(cy->disc);
	t1 = (-cy->b - sqrt_d) / (2.0 * cy->a);
	t2 = (-cy->b + sqrt_d) / (2.0 * cy->a);
	if (t1 > 0.0)
	{
		cy->h_check = vec3_dot(vec3_sub(vec3_add(ray.origin,
						vec3_scale(ray.direction, t1)), cy->center), cy->axis);
		if (fabs(cy->h_check) <= cy->height / 2.0)
			ts = t1;
	}
	if (t2 > 0.0)
	{
		cy->h_check = vec3_dot(vec3_sub(vec3_add(ray.origin,
						vec3_scale(ray.direction, t2)), cy->center), cy->axis);
		if (fabs(cy->h_check) <= cy->height / 2.0)
			ts = min_pos(ts, t2);
	}
	return (ts);
}

static void	setup_cone(t_ray ray, t_cone *co)
{
	co->axis = vec3_norm(co->axis);
	co->oc = vec3_sub(ray.origin, co->tip);
	co->k = co->radius / co->height;
	co->k = co->k * co->k;
	co->dv = vec3_dot(ray.direction, co->axis);
	co->ov = vec3_dot(co->oc, co->axis);
	co->dd = vec3_dot(ray.direction, ray.direction);
	co->od = vec3_dot(co->oc, ray.direction);
	co->oo = vec3_dot(co->oc, co->oc);
}

static double	disc_cone(t_cone *co)
{
	co->a = (1.0 + co->k) * co->dv * co->dv - co->dd;
	co->b = 2.0 * ((1.0 + co->k) * co->dv * co->ov - co->od);
	co->c = (1.0 + co->k) * co->ov * co->ov - co->oo;
	co->disc = co->b * co->b - 4.0 * co->a * co->c;
	return (co->disc);
}

static double	test_cone_side(t_cone *co)
{
	double	t1;
	double	t2;
	double	ts;
	double	sqrt_d;

	ts = -1;
	sqrt_d = sqrt(co->disc);
	t1 = (-co->b - sqrt_d) / (2.0 * co->a);
	t2 = (-co->b + sqrt_d) / (2.0 * co->a);
	if (t1 > 0.0)
	{
		co->h = co->ov + t1 * co->dv;
		if (co->h >= 0.0 && co->h <= co->height)
			ts = t1;
	}
	if (t2 > 0.0)
	{
		co->h = co->ov + t2 * co->dv;
		if (co->h >= 0.0 && co->h <= co->height)
			ts = min_pos(ts, t2);
	}
	return (ts);
}
