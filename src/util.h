#ifndef __UTIL_H_
#define __UTIL_H_

#define M_PI 3.14159265358979323846264338327950288

void Error(const char *function, const char *message);
void SetPixel(int x, int y, Uint32 color);
void Normalize(Vector3f *vector);
void Euler2Vector3f(float yaw, float pitch, Vector3f *vector);
void AddVector3f(Vector3f a, Vector3f b, Vector3f *result);
void ScaleVector3f(Vector3f *v, float factor);
void RotateY(Vector3f *vector, float angle);
void RotateZ(Vector3f *vector, float angle);
float ToRadians(float degrees);

#endif
