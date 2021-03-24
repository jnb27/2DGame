#ifndef __MAGE_H__
#define __MAGE_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf2d_sprite.h"
#include "entity.h"

/**
* @brief spawn a mage entity
* @param position the screen position to spawn the mage at
* @return NULL on error, or a pointer to a new mage entity
*/
Entity *earth_mage_spawn();

Entity *Mage_Team();

void Shopping(Entity *self);

#endif