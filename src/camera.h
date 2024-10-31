#ifndef __CAMERA_
#define __CAMERA_

void CreateCamera(Camera *camera);
// int CastRay(Vector3f origin, Vector3f direction, World world);
void Render(Camera camera, World world);

#endif
