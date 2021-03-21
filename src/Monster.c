#include "simple_logger.h"
#include "Monster.h"

const Uint8 *keys;
void MonsterTeam_Think(Entity *self);
void MonsterActive_think(Entity *self);

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

	monster->EntType = Enemy;
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

	monster->EntType = Enemy;
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

	monster->EntType = Enemy;
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

	monster->EntType = Enemy;
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

	monster->EntType = Enemy;
	monster->ElementType = Fire;
	monster->ActionPoints = 0;
	monster->health = 100;
	monster->mana = 100;
	monster->limit = 0;
	monster->TurnActive = 0;

	//Moveset, High Damage High costs medium hp

	return monster;
}

void MonsterActive_think(Entity *self)
{
	if (!self)return;

	if (self->health == 0)
	{
		entity_free(self);
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_D])
		{
			self->position.x += 3;
		}
		if (keys[SDL_SCANCODE_A])
		{
			self->position.x -= 3;
		}
		if (keys[SDL_SCANCODE_W])
		{
			self->position.y -= 3;
		}
		if (keys[SDL_SCANCODE_S])
		{
			self->position.y += 3;
		}

		if (keys[SDL_SCANCODE_P])
		{
			self->TurnActive = 0;
			self->TurnComplete = 1;
			SDL_Delay(200);
		}
	}
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

	if (self->Member1 == NULL)
	{
		//If my first member is dead and it's not time for shop yet, respawn someone new
		self->Member1 = ice_monster_spawn();
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		//Allowed to do stuff
		self->Member1->TurnActive = 1;
		if (self->Member1->TurnActive == 1 && self->Member1->TurnComplete == 0)
		{
			//Member1 Is allowed to do stuff
			self->Member1->think = MonsterActive_think;
		}
		if (self->Member1->TurnActive == 1 && self->Member1->TurnComplete == 1)
		{
			//Member 1 is done and passes it to Member2
			//self->Member1->think = MageIdle_think;
			self->Member1->TurnActive = 0;
			//self->Member1->TurnComplete = 0; 
			self->Member2->TurnActive = 1;

			//self->Member1->think = MageIdle_think;
		}

		if (self->Member2->TurnActive == 1 && self->Member2->TurnComplete == 0)
		{
			//Member2 is allowed to do stuff
			self->Member2->think = MonsterActive_think;
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
			self->Member3->think = MonsterActive_think;
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
		self->TargetTeam->Member1->TurnComplete = 0;
		self->TargetTeam->Member1->TurnActive = 0;

		self->TargetTeam->Member2->TurnComplete = 0;
		self->TargetTeam->Member2->TurnActive = 0;

		self->TargetTeam->Member3->TurnComplete = 0;
		self->TargetTeam->Member3->TurnActive = 0;
	}
}