#include "minirt.h"



t_vec3 ray_color2(t_ray ray, int depth)
{
    t_vec3 col;
    t_hit hit;
    t_ray shadow_r;
    
    if (check_intersections(ray, &hit))
    {
        shadow_r = cr_ray(hit.p, unit_vector(sub(gen.light.center, hit.p)));
        if (shadow_ray(shadow_r, hit.obj) == 0)
        {
            return add(point_light2(&hit, gen.light, hit.color), gen.ambient_salt);
        }
        else
        {
            return add(vec3(0, 0, 0), gen.ambient_salt);
        }
    }
    return mpv(gen.ambient_color, 0.8);
    return (vec3(0.15, 0.15, 0.15));
}


double reverse_equation(t_ray ray, t_vec3 point)
{
 
  double t = ((point.x - ray.origin.x) * ray.direction.x +
              (point.y - ray.origin.y) * ray.direction.y +
              (point.z - ray.origin.z) * ray.direction.z) /
             (ray.direction.x * ray.direction.x +
              ray.direction.y * ray.direction.y +
              ray.direction.z * ray.direction.z);

    return t;

}

int check_intersections(t_ray ray, t_hit *hit)
{
    t_vec3 col;
    double tmin;
    t_scene *temp;
    temp = gen.scene;
    tmin = -1;
    t_triangle test;
    while (temp)
    {
        int i = 0;        
        while (i < temp->object.mesh->size)
        {
            if (dot(temp->object.mesh->triangles[i].normal, sub(ray.origin, ray.direction)) < 0.0)
            {
                i++;
                continue;
            }
            if (call_back(ray, temp->object.mesh->triangles[i], &(hit->t), hit))
            {
                
                if (tmin == -1 || (hit->t < tmin && hit->t > 0.0))
                {
                    test = temp->object.mesh->triangles[i];
                    tmin = hit->t;
                    hit->normal = temp->object.mesh->triangles[i].normal;
                    hit->normal = interpolateTriangle(test.a.normal, test.b.normal, test.c.normal, hit->u, hit->v);
                    hit->obj = &(temp->object);
                    hit->color = temp->object.color;
                }
            }
            i++;
        }
        temp = temp->next;
    }
    if (tmin != -1)
    {
        hit->p = ray_on_at(ray, tmin); 
        return 1;
    }
    return 0;
}



int shadow_ray(t_ray ray, void *not)
{
    t_hit hit;
    t_scene *temp;

    temp = gen.scene;
    hit.t = -1;
    while (temp)
    {
        int i = 0;

        while (!(&(temp->object) == not) && i < temp->object.mesh->size)
        {
            if (call_back(ray, temp->object.mesh->triangles[i], &(hit.t), &hit))
            {
                if (hit.t > 0.0)
                {
                    double t;
                    t = reverse_equation(ray, gen.light.center);
                    if (t > hit.t)
                        return 1;
                }
            }
            i++;
        }
        temp = temp->next;
    }
    return 0;
}