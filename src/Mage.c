#include "simple_logger.h"

#include "Mage.h"
#include "Item.h"

const Uint8 *keys;

void MageTeam_Think(Entity *self);
void MageActive_think(Entity *self);
void MageIdle_think(Entity *self);

void FireMage_Think(Entity *self);
void WaterMage_Think(Entity *self);
void EarthMage_Think(Entity *self);
void IceMage_Think(Entity *self);
void WindMage_Think(Entity *self);

void HandleInventory(Entity *self);
void SelectTeamMember(Entity *self);
void SelectEnemyMember(Entity *self);
void PickTargetType(Entity *self);

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

	mage->TargetMode = Default;
	mage->think = FireMage_Think;
	mage->target = NULL;
	mage->ElementType = Fire;
	mage->EntType = Party;

	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;
	mage->TurnComplete = 0;

	//Moveset, High Damage High costs medium hp
	//Move 1 : 20 Damage for 10 Mana
	//Move 2 : Buff Next Attack for Double damage on next turn 
	//Move 3 : Something

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

	mage->TargetMode = Default;
	mage->TargetMode = Default;
	mage->think = WaterMage_Think;
	mage->ElementType = Water;
	mage->EntType = Party;

	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//High Healing Kit, High HP, High Mana, Next to no damage
	//Move 1: Heal Ally 
	//Move 2: Damage Enemy 
	//Move 3: Debuff Enemy, lower attack maybe ? half damage on next attack

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

	mage->TargetMode = Default;
	mage->think = EarthMage_Think;
	mage->ElementType = Earth;
	mage->EntType = Party;

	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//Shields ? Maybe debuffs or High HP, Low damage, Low costs
	//Move 1: Damage Enemy
	//Move 2: Shield self
	//Move 3: Defense buff, take reduced damage on another turn

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

	mage->TargetMode = Default;
	mage->think = WindMage_Think;
	mage->ElementType = Wind;
	mage->EntType = Party;

	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//Low HP, Low costs, Multi hit or random damage
	//Move 1: Give someone an extra turn might be hard
	//Move 2: Damage enemy
	//Move 3: Grant someone a free dodge

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

	mage->TargetMode = Default;
	mage->think = IceMage_Think;
	mage->ElementType = Ice;
	mage->EntType = Party;

	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	//Low Hp, High Cost, Extremely High Damage Glass cannon
	//Move 1: Damage enemy 
	//Move 2: Stop an enemy from taking a turn 
	//Move 3: Something

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
			SDL_Delay(350);
		}
	}
}
void MageIdle_think(Entity *self)
{
	if (!self)return;
}

void FireMage_Think(Entity *self)
{
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);
	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{

		if (self->target != NULL)
		{
			if (keys[SDL_SCANCODE_1])
			{
				//Do Move 1
				slog("You attacked Enemy 1");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				slog("You attacked Enemy 2");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				slog("You attacked Enemy 3");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}
		}

		//The following select a target if you don't have one
		if (keys[SDL_SCANCODE_1] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member1;
			slog("Target Enemy 1");
			SDL_Delay(500);
		}

		if (keys[SDL_SCANCODE_2] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member2;
			slog("Target Enemy 2");
			SDL_Delay(350);
		}

		if (keys[SDL_SCANCODE_3] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member3;
			slog("Target Enemy 3");
			SDL_Delay(350);
		}

	}
}

void WaterMage_Think(Entity *self)
{
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);
	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		
		//If I'm targetting a teammate,
		if (self->target != NULL && self->TargetMode == Team && self->target->EntType == Party)
		{
			HandleInventory(self);
		}
		
		//Targetting Friendly Member
		if (self->target == NULL && self->TargetMode == Team)
		{
			SelectTeamMember(self);
		}


		//When you have a target and it's an enemy, attack it
		if (self->target != NULL && self->target->EntType == Enemy)
		{
			if (keys[SDL_SCANCODE_1])
			{
				//Do Move 1
				slog("Water Mage used Attack 1");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				self->target = NULL;
				self->TargetMode = Default;
				slog("WM Turn End");
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				slog("Water Mage used Attack 2");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				self->target = NULL;
				self->TargetMode = Default;
				slog("WM Turn End");
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				slog("Water Mage used Attack 3");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				self->target = NULL;
				self->TargetMode = Default;
				slog("WM Turn End");
				SDL_Delay(350);
			}
		}


		//Once in enemy targetting mode, pick an enemy 1 - 3
		SelectEnemyMember(self);
		PickTargetType(self);

	}
}

void EarthMage_Think(Entity *self)
{
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);
	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{

		if (self->target != NULL)
		{
			if (keys[SDL_SCANCODE_1])
			{
				//Do Move 1
				slog("You attacked Enemy 1");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				slog("You attacked Enemy 2");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				slog("You attacked Enemy 3");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}
		}

		//The following select a target if you don't have one
		if (keys[SDL_SCANCODE_1] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member1;
			slog("Target Enemy 1");
			SDL_Delay(500);
		}

		if (keys[SDL_SCANCODE_2] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member2;
			slog("Target Enemy 2");
			SDL_Delay(350);
		}

		if (keys[SDL_SCANCODE_3] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member3;
			slog("Target Enemy 3");
			SDL_Delay(350);
		}

	}
}

void WindMage_Think(Entity *self)
{
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);
	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{

		if (self->target != NULL)
		{
			if (keys[SDL_SCANCODE_1])
			{
				//Do Move 1
				slog("You attacked Enemy 1");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				slog("You attacked Enemy 2");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				slog("You attacked Enemy 3");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}
		}

		//The following select a target if you don't have one
		if (keys[SDL_SCANCODE_1] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member1;
			slog("Target Enemy 1");
			SDL_Delay(500);
		}

		if (keys[SDL_SCANCODE_2] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member2;
			slog("Target Enemy 2");
			SDL_Delay(350);
		}

		if (keys[SDL_SCANCODE_3] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member3;
			slog("Target Enemy 3");
			SDL_Delay(350);
		}

	}
}

void IceMage_Think(Entity *self)
{
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);
	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{

		if (self->target != NULL)
		{
			if (keys[SDL_SCANCODE_1])
			{
				//Do Move 1
				slog("You attacked Enemy 1");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				slog("You attacked Enemy 2");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				slog("You attacked Enemy 3");
				self->TurnActive = 0;
				self->TurnComplete = 1;
				SDL_Delay(350);
			}
		}

		//The following select a target if you don't have one
		if (keys[SDL_SCANCODE_1] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member1;
			slog("Target Enemy 1");
			SDL_Delay(500);
		}

		if (keys[SDL_SCANCODE_2] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member2;
			slog("Target Enemy 2");
			SDL_Delay(350);
		}

		if (keys[SDL_SCANCODE_3] && self->target == NULL)
		{
			self->target = self->TargetTeam->Member3;
			slog("Target Enemy 3");
			SDL_Delay(350);
		}

	}
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

	team->Member1 = water_mage_spawn();
	team->Member2 = water_mage_spawn();
	team->Member3 = earth_mage_spawn();

	team->Inventory = InventorySpawn();

	team->Member1->Inventory = team->Inventory;
	team->Member2->Inventory = team->Inventory;
	team->Member3->Inventory = team->Inventory;

	team->Member1->FriendlyTeam = team;
	team->Member2->FriendlyTeam = team;
	team->Member3->FriendlyTeam = team;

	return team; 
}

void MageTeam_Think(Entity *self)
{
	if (!self)return;

	self->Member1->TargetTeam = self->TargetTeam;
	self->Member2->TargetTeam = self->TargetTeam;
	self->Member3->TargetTeam = self->TargetTeam;

	if (self->TurnActive == 1 && self->TurnComplete == 0)
	{
		//Allowed to do stuff
		self->Member1->TurnActive = 1;

		if (self->Member1->TurnActive == 1 && self->Member1->TurnComplete == 1)
		{
			//Member 1 is done and passes it to Member2
			self->Member2->TurnActive = 1;
		}

		if (self->Member2->TurnActive == 1 && self->Member2->TurnComplete == 1)
		{
			//Member 2 is done, pass it on
			self->Member3->TurnActive = 1;
		}

		if (self->Member3->TurnActive == 1 && self->Member3->TurnComplete == 1)
		{
			//Member 3 is done, pass it on
			self->Member3->TurnActive = 0;
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


void HandleInventory(Entity *self)
{
	if (self->Inventory->ItemSlot1->quantity < 1 && self->Inventory->ItemSlot2->quantity < 1 && self->Inventory->ItemSlot3->quantity < 1 && self->Inventory->ItemSlot4->quantity < 1 && self->Inventory->ItemSlot5->quantity < 1)
	{
		//If you have no items, then do other stuff.
		self->target = NULL;
		self->TargetMode = Default;
		slog("You have no items to use");
	}


	if (keys[SDL_SCANCODE_1])
	{
		//Check if you have a potion to use, if so then use it
		if (self->Inventory->ItemSlot1->quantity >= 1)
		{
			self->target->health += self->Inventory->ItemSlot1->health;
			self->Inventory->ItemSlot1->quantity -= 1;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage Health potion Party Member1");
			slog("WM Turn End");
		}
		else if (self->Inventory->ItemSlot1->quantity < 1)
		{
			//No more potions, turn is not consumed 
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage cannot use potion, no more potions");
		}
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_2])
	{
		//Check if you have a potion to use, if so then use it
		if (self->Inventory->ItemSlot2->quantity >= 1)
		{
			self->target->mana += self->Inventory->ItemSlot2->mana;
			self->Inventory->ItemSlot2->quantity -= 1;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage mana potion Party Member1");
			slog("WM Turn End");
		}
		else if (self->Inventory->ItemSlot2->quantity < 1)
		{
			//No more potions, turn is not consumed 
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage cannot use potion, no more potions");
		}
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_3])
	{
		//Check if you have a potion to use, if so then use it
		if (self->Inventory->ItemSlot3->quantity >= 1)
		{
			self->target->limit += self->Inventory->ItemSlot3->limit;
			self->Inventory->ItemSlot3->quantity -= 1;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage limit potion Party Member1");
			slog("WM Turn End");
		}
		else if (self->Inventory->ItemSlot3->quantity < 1)
		{
			//No more potions, turn is not consumed 
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage cannot use potion, no more potions");
		}
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_4])
	{
		//Check if you have a potion to use, if so then use it
		if (self->Inventory->ItemSlot4->quantity >= 1)
		{
			self->target->health += self->Inventory->ItemSlot4->health;
			self->target->mana += self->Inventory->ItemSlot4->mana;
			self->Inventory->ItemSlot4->quantity -= 1;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage mix potion Party Member1");
			slog("WM Turn End");
		}
		else if (self->Inventory->ItemSlot4->quantity < 1)
		{
			//No more potions, turn is not consumed 
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage cannot use potion, no more potions");
		}
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_5])
	{
		//Check if you have a potion to use, if so then use it
		if (self->Inventory->ItemSlot5->quantity >= 1)
		{
			self->target->ShieldHP += self->Inventory->ItemSlot5->ShieldHP;
			self->Inventory->ItemSlot5->quantity -= 1;
			self->TurnActive = 0;
			self->TurnComplete = 1;
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage siheld potion Party Member1");
			slog("WM Turn End");
		}
		else if (self->Inventory->ItemSlot5->quantity < 1)
		{
			//No more potions, turn is not consumed 
			self->target = NULL;
			self->TargetMode = Default;
			slog("Water mage cannot use potion, no more potions");
		}
		SDL_Delay(350);
	}
}

void SelectTeamMember(Entity *self)
{
	if (keys[SDL_SCANCODE_1])
	{
		self->target = self->FriendlyTeam->Member1;
		slog("Water mage targetted Party Member1");
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_2])
	{
		self->target = self->FriendlyTeam->Member2;
		slog("Water mage targetted Party Member2");
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_3])
	{
		self->target = self->FriendlyTeam->Member3;
		slog("Water mage targetted Party Member3");
		SDL_Delay(350);
	}
}

void SelectEnemyMember(Entity *self)
{
	if (keys[SDL_SCANCODE_1] && self->target == NULL && self->TargetMode == EnemyT)
	{
		self->target = self->TargetTeam->Member1;
		slog("Water mage Target Enemy 1");
		SDL_Delay(500);
	}

	if (keys[SDL_SCANCODE_2] && self->target == NULL && self->TargetMode == EnemyT)
	{
		self->target = self->TargetTeam->Member2;
		slog("Water mage Target Enemy 2");
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_3] && self->target == NULL && self->TargetMode == EnemyT)
	{
		self->target = self->TargetTeam->Member3;
		slog("Water mage Target Enemy 3");
		SDL_Delay(350);
	}
}

void PickTargetType(Entity *self)
{
	if (keys[SDL_SCANCODE_6] && self->target == NULL && self->TargetMode == Default)
	{
		self->TargetMode = EnemyT;
		slog("Targetting enemy");
		SDL_Delay(350);
	}


	//Going from neutral targetting to item Targetting
	if (keys[SDL_SCANCODE_7] && self->target == NULL && self->TargetMode == Default)
	{
		self->TargetMode = Team;
		slog("Item mode");
		SDL_Delay(350);
	}

	//Reset targetting if mistake made
	if (keys[SDL_SCANCODE_Q] && self->TargetMode != Default)
	{
		self->TargetMode = Default;
		self->target = NULL;
	}
}