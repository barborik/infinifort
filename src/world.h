#ifndef __WORLD_H_
#define __WORLD_H_

void CreateWorld(World *world);
int GetTile(World world, Vector3i position);
void SetTile(World world, Vector3i position, int tile);

#endif
