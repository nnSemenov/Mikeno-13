#! /bin/bash
clear
blockMesh
# refineWallLayer "(gas_wall porous_wall)" 0.6780924
refineWallLayer "(gas_wall porous_wall)" 0.604396
refineWallLayer "(gas_wall porous_wall)" 0.454545

createZones

checkMesh