A cheap fluid-ish simulation which runs on Mobile SDR (Quest 3) pipeline.

![image](https://github.com/Tokusei/Q3_FlowmapParticles/assets/4631534/8855c7dc-3262-40c4-b690-e533fb219d60)


This uses a series of pre-baked textures to simulate particle flow down a river. The maps used in the simulation are:\
\
Mask Map - A B/W map which is used to determine which areas are inside the river\
Flow Map - A custom RT=painted flow map influnce the direction of the particles\
Height Map - Allows for rivers which flow down hills, stepped rivers etc - controls how particles move over waterfalls\
JumpFloodMap - Contains the distance to the nearest surface, and its direction, which lets particles collide/repel from edges\
