#include "simple_logger.h"
#include "Item.h"


Entity *InventorySpawn()
{
	Entity *Inv; 
	Inv = entity_new();

	if (!Inv)
	{
		slog("Not Inventory");
	}

	Inv->ItemSlot1 = HealthPot();
	Inv->ItemSlot2 = ManaPot();
	Inv->ItemSlot3 = LimitBreaker();
	Inv->ItemSlot4 = MixedPot();
	Inv->ItemSlot5 = ShieldPotion();
	return Inv;
}

Entity *HealthPot()
{
	Entity *HP;
	HP = entity_new();
	if (!HP)
	{
		slog("HP broke");
	}

	HP->quantity = 0;
	HP->gold = 10;
	HP->health = 25;
	return HP;

}

Entity *ManaPot()
{
	Entity *MP;
	MP = entity_new();
	if (!MP)
	{
		slog("MP broke");
	}

	MP->quantity = 0;
	MP->gold = 10;
	MP->mana = 25;

	return MP;
}

Entity *LimitBreaker()
{
	Entity *LB;
	LB = entity_new();
	if (!LB)
	{
		slog("LB broke");
	}

	LB->quantity = 0;
	LB->gold = 10;
	LB->health = 25;
	return LB;
}

Entity *MixedPot()
{
	Entity *Mix;
	Mix = entity_new();
	if (!Mix)
	{
		slog("Mix broke");
	}

	Mix->quantity = 0;
	Mix->gold = 10;
	Mix->health = 25;
	Mix->mana = 25;

	return Mix;
}

Entity *ShieldPotion()
{
	Entity *SP;
	SP = entity_new();
	
	if (!SP)
	{
		slog("Shield broke");
	}

	SP->quantity = 1;
	SP->gold = 15;
	SP->ShieldHP = 35;

	return SP;
}