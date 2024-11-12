#ifndef __CAMERA_H_
#define __CAMERA_H_

void CreateCamera(Camera *camera);
// int CastRay(Vector3f origin, Vector3f direction, World world);
void Render(Camera camera, World world);

#endif
