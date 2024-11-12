#ifndef __WORLD_H_
#define __WORLD_H_

void CreateWorld(World *world);
int GetVoxel(World world, Vector3i position);
void SetVoxel(World world, Vector3i position, int voxel);

#endif
