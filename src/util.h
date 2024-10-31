#ifndef __UTIL_
#define __UTIL_

void Error(const char *function, const char *message);
void SetPixel(int x, int y, Uint32 color);
void Normalize(Vector3f *vector);
float ToRadians(float degrees);

#endif
