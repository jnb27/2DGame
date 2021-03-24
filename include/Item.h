#ifndef __ITEM_H__
#define __ITEM_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf2d_sprite.h"
#include "entity.h"

Entity *HealthPot();
Entity *ManaPot();
Entity *MixedPot();
Entity *ShieldPotion();
Entity *LimitBreaker();
Entity *InventorySpawn();

Entity *ShopHP();
Entity *ShopMana();
Entity *ShopLimit();
Entity *ShopMix();
Entity *ShopShield();

#endif