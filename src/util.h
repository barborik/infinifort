#ifndef __UTIL_
#define __UTIL_

#define M_PI 3.14159265358979323846264338327950288

void Error(const char *function, const char *message);
void SetPixel(int x, int y, Uint32 color);
void Normalize(Vector3f *vector);
float ToRadians(float degrees);

#endif
