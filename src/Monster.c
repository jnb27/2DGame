#include "simple_logger.h"
#include "Monster.h"

void MonsterTeam_Think(Entity *self);

Entity *fire_monster_spawn()
{
	Entity *monster;
	monster = entity_new();
	if (!monster)
	{
		slog("failed to create test");
		return NULL;
	}
	monster->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	monster->frameRate = 0.1;
	monster->frameCount = 8;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 240;
	monster->position.y = 240;

	monster->ElementType = Fire;
	monster->ActionPoints = 0;
	monster->health = 100;
	monster->mana = 100;
	monster->limit = 0;
	monster->TurnActive = 0;

	//Moveset, High Damage High costs medium hp

	return monster;
}

Entity *water_monster_spawn()
{
	Entity *monster;
	monster = entity_new();
	if (!monster)
	{
		slog("failed to create test");
		return NULL;
	}
	monster->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	monster->frameRate = 0.1;
	monster->frameCount = 8;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 480;
	monster->position.y = 240;

	monster->ElementType = Fire;
	monster->ActionPoints = 0;
	monster->health = 100;
	monster->mana = 100;
	monster->limit = 0;
	monster->TurnActive = 0;
	monster->radius = 54;

	//Moveset, High Damage High costs medium hp

	return monster;
}

Entity *earth_monster_spawn()
{
	Entity *monster;
	monster = entity_new();
	if (!monster)
	{
		slog("failed to create test");
		return NULL;
	}
	monster->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	monster->frameRate = 0.1;
	monster->frameCount = 8;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 360;

	monster->ElementType = Fire;
	monster->ActionPoints = 0;
	monster->health = 100;
	monster->mana = 100;
	monster->limit = 0;
	monster->TurnActive = 0;

	//Moveset, High Damage High costs medium hp

	return monster;
}

Entity *wind_monster_spawn()
{
	Entity *monster;
	monster = entity_new();
	if (!monster)
	{
		slog("failed to create test");
		return NULL;
	}
	monster->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	monster->frameRate = 0.1;
	monster->frameCount = 8;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 120;

	monster->ElementType = Fire;
	monster->ActionPoints = 0;
	monster->health = 100;
	monster->mana = 100;
	monster->limit = 0;
	monster->TurnActive = 0;

	//Moveset, High Damage High costs medium hp

	return monster;
}

Entity *ice_monster_spawn()
{
	Entity *monster;
	monster = entity_new();
	if (!monster)
	{
		slog("failed to create test");
		return NULL;
	}
	monster->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	monster->frameRate = 0.1;
	monster->frameCount = 8;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 240;

	monster->ElementType = Fire;
	monster->ActionPoints = 0;
	monster->health = 100;
	monster->mana = 100;
	monster->limit = 0;
	monster->TurnActive = 0;

	//Moveset, High Damage High costs medium hp

	return monster;
}

void monster_think(Entity *self)
{

}

Entity *Monster_Team()
{
	Entity *team;
	team = entity_new();

	if (!team)
	{
		slog("Failed to make a team");
		return NULL;
	}

	team->think = MonsterTeam_Think;
	team->TurnActive = 0;
	team->TurnComplete = 0;
	team->Member1 = ice_monster_spawn();
	team->Member2 = wind_monster_spawn();
	team->Member3 = earth_monster_spawn();

	return team;
}

void MonsterTeam_Think(Entity *self)
{
	if (!self)return;

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		//Allowed to do stuff
	}

	if (self->TurnActive == 1 && self->TurnComplete == 1)
	{
		//If it is my turn and I have completed it, make the enemy team active, myself inactive, and my turn is no longer complete. 
		self->TargetTeam->TurnActive = 1;
		self->TurnActive = 0;
		self->TurnComplete = 0;
	}
}