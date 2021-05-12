#include "simple_logger.h"
#include "Monster.h"
#include "Item.h"

const Uint8 *keys;
void MonsterTeam_Think(Entity *self);
void MonsterActive_think(Entity *self);
void FireMonsterThink(Entity *self);
void IceMonsterThink(Entity *self);
void WaterMonsterThink(Entity *self);
void EarthMonsterThink(Entity *self);
void WindMonsterThink(Entity *self);

void MonsterDeath(Entity *self);

Entity *fire_monster_spawn()
{
	Entity *monster;
	monster = entity_new();
	if (!monster)
	{
		slog("failed to create test");
		return NULL;
	}
	monster->sprite = gf2d_sprite_load_all("images/enemies/FlameMonster.png", 130, 146, 1);
	monster->frameRate = 0.1;
	monster->frameCount = 1;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 240;

	monster->think = FireMonsterThink;
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
	monster->sprite = gf2d_sprite_load_all("images/enemies/WaterMonster.jpg", 100, 200, 3);
	monster->frameRate = 0.1;
	monster->frameCount = 12;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 240;

	monster->think = WaterMonsterThink;
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
	monster->sprite = gf2d_sprite_load_all("images/enemies/EarthMonster.png", 96, 96, 4);
	monster->frameRate = 0.1;
	monster->frameCount = 16;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 360;

	monster->think = EarthMonsterThink;
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
	monster->sprite = gf2d_sprite_load_all("images/enemies/WindMonster.png", 100, 154, 8);
	monster->frameRate = 0.1;
	monster->frameCount = 24;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 120;

	monster->think = WindMonsterThink;
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
	monster->sprite = gf2d_sprite_load_all("images/enemies/IceMonster.png", 110, 110, 6);
	monster->frameRate = 0.1;
	monster->frameCount = 24;
	//monster->update = player_update;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 240;

	monster->think = IceMonsterThink;
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
		int rando = (gfc_random() * 3) + 1;
		slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->TargetTeam->Member1;
			self->target->health -= 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->TargetTeam->Member2;
			self->target->health -= 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->TargetTeam->Member3;
			self->target->health -= 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
	}
}

void FireMonsterThink(Entity *self)
{
	if (!self)return;

	if (self->health <= 0)
	{
		MonsterDeath(self);
		slog("Fire monster down");
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		int rando = (gfc_random() * 3) + 1;
		slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->TargetTeam->Member1;
			self->target->health -= 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Fire monster cast Blaze on Team member 1. Team Member Health:");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->TargetTeam->Member2;
			self->target->health -= 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Fire monster cast Blaze on Team member 2. Team Member Health:");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->TargetTeam->Member3;
			self->target->health -= 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Fire monster cast Blaze on Team member 3. Team Member Health:");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
	}
}

void IceMonsterThink(Entity *self)
{
	if (!self)return;

	if (self->health <= 0)
	{
		MonsterDeath(self);
		slog("Ice monster down");
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		int rando = (gfc_random() * 3) + 1;
		//slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->TargetTeam->Member1;
			self->target->mana -= 10;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Ice Monster cast Permafrost on Team Member 1, Team member Mana remaining : ");
			slog("%i", self->target->mana);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->TargetTeam->Member2;
			self->target->mana -= 10;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Ice Monster cast Permafrost on Team Member 2, Team member Mana remaining : ");
			slog("%i", self->target->mana);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->TargetTeam->Member3;
			self->target->mana -= 10;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Ice Monster cast Permafrost on Team Member 3, Team member Mana remaining : ");
			slog("%i", self->target->mana);
			SDL_Delay(200);
		}
	}
}

void WaterMonsterThink(Entity *self)
{
	if (!self)return;

	if (self->health <= 0)
	{
		MonsterDeath(self);
		slog("Water monster down");
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		int rando = (gfc_random() * 3) + 1;
		slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->FriendlyTeam->Member1;
			self->target->health += 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Water monster healed their party member 1, new health : ");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->FriendlyTeam->Member2;
			self->target->health += 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Water monster healed their party member 1, new health : ");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->FriendlyTeam->Member3;
			self->target->health += 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Water monster healed their party member 1, new health : ");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
	}
}

void EarthMonsterThink(Entity *self)
{
	if (!self)return;

	if (self->health <= 0)
	{
		MonsterDeath(self);
		slog("Earth monster down");
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		int rando = (gfc_random() * 3) + 1;
		slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->TargetTeam->Member1;
			self->target->health += 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Dumb Rock healed your Team Member 1, new health: ");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->TargetTeam->Member2;
			self->target->health += 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Dumb Rock healed your Team Member 2, new health: ");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->TargetTeam->Member3;
			self->target->health += 15;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("Dumb Rock healed your Team Member 3, new health : ");
			slog("%i", self->target->health);
			SDL_Delay(200);
		}
	}
}

void WindMonsterThink(Entity *self)
{
	if (!self)return;

	if (self->health <= 0)
	{
		MonsterDeath(self);
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		int rando = (gfc_random() * 5) + 1;
		//slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->TargetTeam->Inventory;
			if (self->target->ItemSlot1->quantity >= 1)
			{
				self->target->ItemSlot1->quantity -= 1;
				slog("Wind Monster stole a health pot remaining: ");
			}
			else{
				slog("Wind monster tried to steal a health pot but failed!");
			}
			
			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->quantity);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->TargetTeam->Inventory;
			if (self->target->ItemSlot2->quantity >= 1)
			{
				self->target->ItemSlot2->quantity -= 1;
				slog("Wind Monster stole a mana pot remaining: ");
			}
			else{
				slog("Wind monster tried to steal a mana pot but failed!");
			}

			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->quantity);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->TargetTeam->Inventory;
			if (self->target->ItemSlot3->quantity >= 1)
			{
				self->target->ItemSlot3->quantity -= 1;
				slog("Wind Monster stole a limit pot remaining: ");
			}
			else{
				slog("Wind monster tried to steal a limit pot but failed!");
			}

			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->quantity);
			SDL_Delay(200);
		}
		else if (rando == 4)
		{
			self->target = self->TargetTeam->Inventory;
			if (self->target->ItemSlot4->quantity >= 1)
			{
				self->target->ItemSlot4->quantity -= 1;
				slog("Wind Monster stole a mix pot remaining: ");
			}
			else{
				slog("Wind monster tried to steal a mix pot but failed!");
			}

			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->quantity);
			SDL_Delay(200);
		}
		else if (rando == 5)
		{
			self->target = self->TargetTeam->Inventory;
			if (self->target->ItemSlot5->quantity >= 1)
			{
				self->target->ItemSlot5->quantity -= 1;
				slog("Wind Monster stole a shield pot remaining: ");
			}
			else{
				slog("Wind monster tried to steal a shield pot but failed!");
			}

			self->TurnActive = 0;
			self->TurnComplete = 1;
			slog("%i", self->target->quantity);
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
	team->Member1 = wind_monster_spawn();
	team->Member2 = earth_monster_spawn();
	team->Member3 = fire_monster_spawn();

	team->Member1->FriendlyTeam = team;
	team->Member2->FriendlyTeam = team;
	team->Member3->FriendlyTeam = team;

	return team;
}


void MonsterTeam_Think(Entity *self)
{
	if (!self)return;

	//slog("Monster Team Thonk");
	

	//Theoretical code for waving not ready yet, 
	if (self->Member1->health <= 0 &&  self->deaths <= 30)
	{
		//If my first member is dead and it's not time for shop yet, respawn someone new
		self->Member1 = NULL;
		self->Member1 = RandomSpawn();
	}
	if (self->Member2->health <= 0  && self->deaths <= 30)
	{
		//If my first member is dead and it's not time for shop yet, respawn someone new
		self->Member2 = NULL;
		self->Member2 = RandomSpawn();
	}
	if (self->Member3->health <= 0  && self->deaths <= 30)
	{
		//If my first member is dead and it's not time for shop yet, respawn someone new
		self->Member3 = NULL;
		self->Member3 = RandomSpawn();
	}

	if (self->Member1 != NULL && self->Member2 != NULL && self->Member3 != NULL)
	{

		self->Member1->TargetTeam = self->TargetTeam;
		self->Member2->TargetTeam = self->TargetTeam;
		self->Member3->TargetTeam = self->TargetTeam;

		self->Member1->FriendlyTeam = self;
		self->Member2->FriendlyTeam = self;
		self->Member3->FriendlyTeam = self;

		AdjustPositions(self);
	}

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		//Allowed to do stuff
		self->Member1->TurnActive = 1;
		if (self->Member1->TurnActive == 1 && self->Member1->TurnComplete == 0)
		{
			//Member1 Is allowed to do stuff
			//self->Member1->think = MonsterActive_think;
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
			//self->Member2->think = MonsterActive_think;
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
			//self->Member3->think = MonsterActive_think;
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

Entity *RandomSpawn()
{
	Entity *Spawn;

	if (!Spawn)
	{
		slog("Something went wrong");
		return;
	}

	int ran = (gfc_random() * 5) + 1;

	if (ran == 1)
	{
		Spawn = fire_monster_spawn();
		slog("New fire arrived");
	}
	else if (ran == 2)
	{
		Spawn = ice_monster_spawn();
		slog("New ice arrived");
	}
	else if (ran == 3)
	{
		Spawn = wind_monster_spawn();
		slog("New wind arrived");
	}
	else if (ran == 4)
	{
		Spawn = earth_monster_spawn();
		slog("New earth arrived");
	}
	else if (ran == 5)
	{
		Spawn = water_monster_spawn();
		slog("New water arrived");
	}
	return Spawn;
}

void MonsterDeath(Entity *self)
{
	//Drop gold, drop items, 
	self->FriendlyTeam->TargetTeam->gold += 15;
	self->FriendlyTeam->deaths += 5;

	//Random chance to drop loot
	int ran = (gfc_random() * 10) + 1;

	if (ran >= 6)
	{
		//Drop an item
		slog("Time to drop an item");
		int itemnum = (gfc_random() * 5) + 1;
		int randomx = (int)(gfc_random() * 100) + 900;
		int randomy = (int)(gfc_random() * 200) + 100;

		switch (itemnum){
		default:
			slog("You hit default");
		case 1:
			//Drop a health pot at a random spot 
			slog("HP dropped");
			self->FriendlyTeam->ActiveDrop1 = ShopHP();
			self->FriendlyTeam->ActiveDrop1->position.x = randomx;
			self->FriendlyTeam->ActiveDrop1->position.y = randomy;
			break;
		case 2:
			slog("mana");
			self->FriendlyTeam->ActiveDrop2 = ShopMana();
			self->FriendlyTeam->ActiveDrop2->position.x = randomx;
			self->FriendlyTeam->ActiveDrop2->position.y = randomy;
			break;
		case 3:
			slog("limit");
			self->FriendlyTeam->ActiveDrop3 = ShopLimit();
			self->FriendlyTeam->ActiveDrop3->position.x = randomx;
			self->FriendlyTeam->ActiveDrop3->position.y = randomy;
			break;
		case 4: 
			slog("mix");
			self->FriendlyTeam->ActiveDrop4 = ShopMix();
			self->FriendlyTeam->ActiveDrop4->position.x = randomx;
			self->FriendlyTeam->ActiveDrop4->position.y = randomy;
			break;
		case 5: 
			slog("shield");
			self->FriendlyTeam->ActiveDrop5 = ShopShield();
			self->FriendlyTeam->ActiveDrop5->position.x = randomx;
			self->FriendlyTeam->ActiveDrop5->position.y = randomy;
			break;
		}
	}

	slog("A monster has died");
	entity_free(self);
}