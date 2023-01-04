#include "minirt.h"




void smooth(t_mesh *mesh)
{
    int i;

    i = 0;
    while (i < mesh->size)
    {
        mesh->triangles[i].a.normal = vec3(0, 0, 0);
        mesh->triangles[i].b.normal = vec3(0, 0, 0);
        mesh->triangles[i].c.normal = vec3(0, 0, 0);
        i++;
    }
    i = 0;
    while (i < mesh->size)
    {
        mesh->triangles[i].a.normal = add(mesh->triangles[i].a.normal, mesh->triangles[i].normal);
        mesh->triangles[i].b.normal = add(mesh->triangles[i].b.normal, mesh->triangles[i].normal);
        mesh->triangles[i].c.normal = add(mesh->triangles[i].c.normal, mesh->triangles[i].normal);
        i++;
    }
    i = 0;
    while (i < mesh->size)
    {
        mesh->triangles[i].a.normal = unit_vector(mesh->triangles[i].a.normal);
        mesh->triangles[i].b.normal = unit_vector(mesh->triangles[i].b.normal);
        mesh->triangles[i].c.normal = unit_vector(mesh->triangles[i].c.normal);
        i++;
    }
}



float interpolate(float a, float b, float t) 
{
  return a * (1.0 - t) + b * t;
}
t_vec3 interpolate_2(t_vec3 a, t_vec3 b, float t) 
{
  return vec3(interpolate(a.x, b.x, t), interpolate(a.y, b.y, t), interpolate(a.z, b.z, t));
}

t_vec3 interpolateTriangle(t_vec3 a, t_vec3 b, t_vec3 c, float u, float v) 
{
  return add(add(mpv(a , u), mpv(b, v)), mpv(c, 1.0 - u - v));
}
