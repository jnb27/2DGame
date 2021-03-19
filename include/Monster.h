#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf2d_sprite.h"
#include "entity.h"


Entity *fire_monster_spawn();

Entity *water_monster_spawn();

Entity *earth_monster_spawn();

Entity *wind_monster_spawn();

Entity *ice_monster_spawn();

Entity *Monster_Team();

#endif