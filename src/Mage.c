#include "simple_logger.h"

#include "Mage.h"

const Uint8 *keys;
void MageTeam_Think(Entity *self);
void MageActive_think(Entity *self);
void MageIdle_think(Entity *self);

Entity *fire_mage_spawn()
{
	Entity *mage;
	mage = entity_new();
	if (!mage)
	{
		slog("failed to create test");
		return NULL;
	}
	mage->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	mage->frameRate = 0.1;
	mage->frameCount = 8;
	//mage->update = player_update;
	mage->rotation.x = 64;
	mage->rotation.y = 64;
	mage->position.x = 240;
	mage->position.y = 240;

	
	mage->ElementType = Fire;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//Moveset, High Damage High costs medium hp

	return mage;
}

Entity *water_mage_spawn()
{
	Entity *mage;
	mage = entity_new();
	if (!mage)
	{
		slog("failed to create test");
		return NULL;
	}
	mage->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	mage->frameRate = 0.1;
	mage->frameCount = 8;
	//mage->update = player_update;
	mage->rotation.x = 64;
	mage->rotation.y = 64;
	mage->position.x = 240;
	mage->position.y = 120;

	mage->ElementType = Water;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//High Healing Kit, High HP, High Mana, Next to no damage

	return mage;
}

Entity *earth_mage_spawn()
{
	Entity *mage;
	mage = entity_new();
	if (!mage)
	{
		slog("failed to create test");
		return NULL;
	}
	mage->sprite = gf2d_sprite_load_all("images/enemies/Earthmage.png", 85, 94, 4);
	mage->frameRate = 0.1;
	mage->frameCount = 8;
	//mage->update = player_update;
	mage->rotation.x = 64;
	mage->rotation.y = 64;
	mage->position.x = 240;
	mage->position.y = 360;

	mage->ElementType = Earth;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//Shields ? Maybe debuffs or High HP, Low damage, Low costs

	return mage;
}

Entity *wind_mage_spawn(Vector2D position)
{
	Entity *mage;
	mage = entity_new();
	if (!mage)
	{
		slog("failed to create test");
		return NULL;
	}
	mage->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	mage->frameRate = 0.1;
	mage->frameCount = 8;
	//mage->update = player_update;
	mage->rotation.x = 64;
	mage->rotation.y = 64;
	mage->position.x = 240;
	mage->position.y = 240;

	mage->ElementType = Wind;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//Low HP, Low costs, Multi hit or random damage

	return mage;
}

Entity *ice_mage_spawn(Vector2D position)
{
	Entity *mage;
	mage = entity_new();
	if (!mage)
	{
		slog("failed to create test");
		return NULL;
	}
	mage->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	mage->frameRate = 0.1;
	mage->frameCount = 8;
	//mage->update = player_update;
	mage->rotation.x = 64;
	mage->rotation.y = 64;
	mage->position.x = 240;
	mage->position.y = 240;

	mage->ElementType = Ice;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//Low Hp, High Cost, Extremely High Damage Glass cannon

	return mage;
}

void MageActive_think(Entity *self)
{
	if (!self)return;
	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_D])
		{
			self->position.x += 10;
			self->TurnActive = 0;
			self->TurnComplete = 1;
		}
		if (keys[SDL_SCANCODE_A])
		{
			self->position.x -= 10;
		}
		if (keys[SDL_SCANCODE_W])
		{
			self->position.y -= 10;
		}
		if (keys[SDL_SCANCODE_S])
		{
			self->position.y += 10;
		}
	}
}
void MageIdle_think(Entity *self)
{
	if (!self)return;
}


Entity *Mage_Team()
{
	Entity *team;
	team = entity_new();

	if (!team)
	{
		slog("Failed to make a team");
		return NULL;
	}

	team->think = MageTeam_Think;
	team->TurnActive = 0;
	team->TurnComplete = 0;
	team->Member1 = fire_mage_spawn();
	team->Member2 = water_mage_spawn();
	team->Member3 = earth_mage_spawn();

	return team; 
}

void MageTeam_Think(Entity *self)
{
	if (!self)return;

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		//Allowed to do stuff
		self->Member1->TurnActive = 1;
		if (self->Member1->TurnActive == 1 && self->Member1->TurnComplete == 0)
		{
			//Member1 Is allowed to do stuff
			self->Member1->think = MageActive_think;
		}
		if (self->Member1->TurnActive == 1 && self->Member1->TurnComplete == 1)
		{
			//Member 1 is done and passes it to Member2
			self->Member1->think = MageIdle_think;
			self->Member1->TurnActive = 0;
			//self->Member1->TurnComplete = 0; 
			self->Member2->TurnActive = 1;

			//self->Member1->think = MageIdle_think;
		}

		if (self->Member2->TurnActive == 1 && self->Member2->TurnComplete == 0)
		{
			//Member2 is allowed to do stuff
			self->Member2->think = MageActive_think;
		}
		else if (self->Member2->TurnActive == 1 && self->Member2->TurnComplete == 1)
		{
			//Member 2 is done, pass it on
			self->Member2->TurnActive = 0;
			self->Member3->TurnActive = 1;
			//self->Member2->think = MageIdle_think;
		}

		if (self->Member3->TurnActive == 1 && self->Member3->TurnComplete == 0)
		{
			//Member3 is allowed to do stuff
			self->Member3->think = MageActive_think;
		}
		else if (self->Member3->TurnActive == 1 && self->Member3->TurnComplete == 1)
		{
			//Member 3 is done, pass it on
			self->Member3->TurnActive = 0;
			//self->Member3->think = MageIdle_think;

			//If Member 3 has made their turn we must make the team complete and pass it on.
			self->TurnComplete = 1;
		}
	}

	if (self->TurnActive == 1 && self->TurnComplete == 1)
	{
		//If it is my turn and I have completed it, make the enemy team active, myself inactive, and my turn is no longer complete. 
		self->TargetTeam->TurnActive = 1;
		self->TargetTeam->TurnComplete = 0;
		self->TurnActive = 0;
		self->TurnComplete = 0;
	}
}