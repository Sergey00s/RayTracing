#include "minirt.h"


float rad_to_deg(float rad)
{
  float degrees;

  degrees = rad * 180.0 / PI;
  return degrees;
}

int sign(float x)
{
  if (x >= 0)
  {
    return 1;
  }
  return -1;
}

void rotateX(double* x, double* y, double* z, double angle) 
{
  float rad = angle * PI / 180.0;
  float cos_a = cos(rad);
  float sin_a = sin(rad);
  float newY = *y * cos_a - *z * sin_a;
  float newZ = *y * sin_a + *z * cos_a;
  *y = newY;
  *z = newZ;
}


void rotateY(double* x, double* y, double* z, double angle) 
{
  float rad = angle * PI / 180.0;
  float cos_a = cos(rad);
  float sin_a = sin(rad);
  float newX = *x * cos_a + *z * sin_a;
  float newZ = -*x * sin_a + *z * cos_a;
  *x = newX;
  *z = newZ;
}


void rotateZ(double* x, double* y, double* z, float angle) 
{
  float rad = angle * PI / 180.0;
  float cos_a = cos(rad);
  float sin_a = sin(rad);
  float newX = *x * cos_a - *y * sin_a;
  float newY = *x * sin_a + *y * cos_a;
  *x = newX;
  *y = newY;
}



t_vec3 direction_to_angle(t_vec3 dir)
{
 double angle_xy = atan2(dir.y, dir.x);
  double angle_yz = acos(dir.z / sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z));
  double angle_xz = atan2(dir.z, dir.x);
  double angle_xy_degrees = angle_xy * 180.0 / PI;
  double angle_yz_degrees = angle_yz * 180.0 / PI;
  double angle_xz_degrees = angle_xz * 180.0 / PI;
  return vec3(angle_xy_degrees, angle_yz_degrees, angle_xz_degrees);
}


void rotate(t_mesh *mesh, float angle, int axis)
{
  int i;

  i = 0;
  while (i < mesh->size)
  {
    if (axis == 0)
    {
      rotateX(&mesh->triangles[i].a.p.x, &mesh->triangles[i].a.p.y, &mesh->triangles[i].a.p.z, angle);
      rotateX(&mesh->triangles[i].b.p.x, &mesh->triangles[i].b.p.y, &mesh->triangles[i].b.p.z, angle);
      rotateX(&mesh->triangles[i].c.p.x, &mesh->triangles[i].c.p.y, &mesh->triangles[i].c.p.z, angle);
    }
    else if (axis == 1)
    {
       rotateY(&mesh->triangles[i].a.p.x, &mesh->triangles[i].a.p.y, &mesh->triangles[i].a.p.z, angle);
       rotateY(&mesh->triangles[i].b.p.x, &mesh->triangles[i].b.p.y, &mesh->triangles[i].b.p.z, angle);
       rotateY(&mesh->triangles[i].c.p.x, &mesh->triangles[i].c.p.y, &mesh->triangles[i].c.p.z, angle);
    }
    else if (axis == 2)
    {
       rotateZ(&mesh->triangles[i].a.p.x, &mesh->triangles[i].a.p.y, &mesh->triangles[i].a.p.z, angle);
       rotateZ(&mesh->triangles[i].b.p.x, &mesh->triangles[i].b.p.y, &mesh->triangles[i].b.p.z, angle);
       rotateZ(&mesh->triangles[i].c.p.x, &mesh->triangles[i].c.p.y, &mesh->triangles[i].c.p.z, angle);
    }
    i++;
  }
}

void rotate_by_directions(t_mesh *mesh, t_vec3 norms) 
{
    t_vec3 angles;

    angles = direction_to_angle(norms);
    rotate(mesh, 90 - angles.y, 0);    
    rotate(mesh, 90 - angles.x, 2);    
}
