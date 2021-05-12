#include "simple_logger.h"

#include "Mage.h"
#include "Item.h"
#include "gfc_audio.h"

const Uint8 *keys;

void MageTeam_Think(Entity *self);
void MageActive_think(Entity *self);
void MageIdle_think(Entity *self);

void FireMage_Think(Entity *self);
void WaterMage_Think(Entity *self);
void EarthMage_Think(Entity *self);
void IceMage_Think(Entity *self);
void WindMage_Think(Entity *self);

void Fireball(Entity *self, Entity *target);
void FlameBreath(Entity *self);

void Splash(Entity *self, Entity *target);

void RockThrow(Entity *self, Entity *target);

void IceSpike(Entity *self, Entity *target);
void Blizzard(Entity *self);
void AbsZero(Entity *self, Entity *target);

void Gust(Entity *self, Entity *target);
void Whirlwind(Entity *self);

void HandleInventory(Entity *self);
void SelectTeamMember(Entity *self);
void SelectEnemyMember(Entity *self);
void PickTargetType(Entity *self);
void EndTurn(Entity *self);

void MasteryCheck(Entity *self, int SkillCheck);



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

	mage->InventoryLock = 0;
	mage->TargetMode = Default;
	mage->think = FireMage_Think;
	mage->target = NULL;
	mage->ElementType = Fire;
	mage->EntType = Party;

	mage->DoubleDMG = 1;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;
	mage->TurnComplete = 0;

	mage->SkillLevel1 = 1;
	mage->SkillLevel2 = 1;
	mage->SkillLevel3 = 1;
	mage->SkillLevel4 = 1;
	mage->SkillLevel5 = 1;
	//Moveset, High Damage High costs medium hp
	//Move 1 : 20 Damage for 10 Mana
	//Move 2 : Buff Next Attack for Double damage on next turn 
	//Move 3 : Something

	Sound *FlameAttack = gfc_sound_load("music/FlameArrow.mp3", 0.5, 1);
	mage->Audio1 = FlameAttack;

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

	mage->InventoryLock = 0;
	mage->TargetMode = Default;
	mage->TargetMode = Default;
	mage->think = WaterMage_Think;
	mage->ElementType = Water;
	mage->EntType = Party;

	mage->DoubleDMG = 1;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	mage->SkillLevel1 = 1;
	mage->SkillLevel2 = 1;
	mage->SkillLevel3 = 1;
	mage->SkillLevel4 = 1;
	mage->SkillLevel5 = 1;

	Sound *WaterSplash = gfc_sound_load("music/Drip.mp3", 0.5, 1);
	mage->Audio1 = WaterSplash;

	Sound *SingleHeal = gfc_sound_load("music/Heal.wav", 0.5, 1);
	mage->Audio2 = SingleHeal;

	Sound *LargeHeal = gfc_sound_load("music/MegaHeal.wav", 0.5, 1);
	mage->Audio3 = LargeHeal;

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

	mage->InventoryLock = 0;
	mage->TargetMode = Default;
	mage->think = EarthMage_Think;
	mage->ElementType = Earth;
	mage->EntType = Party;

	mage->DoubleDMG = 1;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	mage->SkillLevel1 = 1;
	mage->SkillLevel2 = 1;
	mage->SkillLevel3 = 1;
	mage->SkillLevel4 = 1;
	mage->SkillLevel5 = 1;

	Sound *RockThrow = gfc_sound_load("music/RockThrow.wav", 0.5, 1);
	mage->Audio1 = RockThrow;

	Sound *Shield = gfc_sound_load("music/Shield.wav", 0.5, 1);
	mage->Audio2 = Shield;

	Sound *HyperShield = gfc_sound_load("music/HyperShield.wav", 0.5, 1);
	mage->Audio3 = HyperShield;
	//Shields ? Maybe debuffs or High HP, Low damage, Low costs
	//Move 1: Damage Enemy
	//Move 2: Shield self
	//Move 3: Defense buff, take reduced damage on another turn

	return mage;
}

Entity *wind_mage_spawn()
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

	mage->InventoryLock = 0;
	mage->TargetMode = Default;
	mage->think = WindMage_Think;
	mage->ElementType = Wind;
	mage->EntType = Party;

	mage->DoubleDMG = 1;
	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	mage->SkillLevel1 = 1;
	mage->SkillLevel2 = 1;
	mage->SkillLevel3 = 1;
	mage->SkillLevel4 = 1;
	mage->SkillLevel5 = 1;
	//Low HP, Low costs, Multi hit or random damage
	//Move 1: Give someone an extra turn might be hard
	//Move 2: Damage enemy
	//Move 3: Grant someone a free dodge
	Sound *WindAttack = gfc_sound_load("music/Wind.mp3", 0.5, 1);
	mage->Audio1 = WindAttack;

	Sound *Whirlwind = gfc_sound_load("music/Thunder.wav", 0.5, 1);
	mage->Audio2 = Whirlwind;

	Sound *Coin = gfc_sound_load("music/Coin.wav", 0.5, 1);
	mage->Audio3 = Coin;
	return mage;
}

Entity *ice_mage_spawn()
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

	mage->InventoryLock = 0;
	mage->DoubleDMG = 1;
	mage->TargetMode = Default;
	mage->think = IceMage_Think;
	mage->ElementType = Ice;
	mage->EntType = Party;

	mage->ActionPoints = 0;
	mage->health = 100;
	mage->mana = 100;
	mage->limit = 0;
	mage->TurnActive = 0;

	mage->SkillLevel1 = 1;
	mage->SkillLevel2 = 1;
	mage->SkillLevel3 = 1;
	mage->SkillLevel4 = 1;
	mage->SkillLevel5 = 1;

	Sound *IceS = gfc_sound_load("music/Ice.wav", 0.5, 1);
	mage->Audio1 = IceS;

	Sound *Blizz = gfc_sound_load("music/Hail.wav", 0.5, 1);
	mage->Audio2 = Blizz;

	Sound *Abs = gfc_sound_load("music/IceHit.wav", 0.5, 1);
	mage->Audio3 = Abs;

	//Low Hp, High Cost, Extremely High Damage Glass cannon
	//Move 1: Damage enemy 
	//Move 2: Stop an enemy from taking a turn 
	//Move 3: Something

	return mage;
}

void MageActive_think(Entity *self)
{
	if (!self)return;
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

		if (self->TargetMode == Shop)
		{
			Shopping(self);
		}

		//When you have a target and it's an enemy, attack it
		if (self->target != NULL && self->target->EntType == Enemy)
		{
			if (keys[SDL_SCANCODE_1])
			{
				Fireball(self, self->target);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_2])
			{
				FlameBreath(self);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_3])
			{
				slog("Fire Mage used Phoenix Dance, Damage on next hit 2x");
				self->DoubleDMG = 2;
				EndTurn(self);
			}
		}

		//Once in enemy targetting mode, pick an enemy 1 - 3
		SelectEnemyMember(self);
		PickTargetType(self);
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

		if (self->TargetMode == Shop)
		{
			Shopping(self);
		}

		//When you have a target and it's an enemy, attack it
		if (self->target != NULL && self->target->EntType == Enemy)
		{
			if (keys[SDL_SCANCODE_1])
			{
				Splash(self, self->target);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				self->target == NULL; 
				SelectTeamMember(self);
				self->target->health += 20;
				self->mana -= 20;
				slog("Water Mage used heal");
				gfc_sound_play(self->Audio2, 0, 1, 2, -1);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				self->FriendlyTeam->Member1->health += 10;
				self->FriendlyTeam->Member2->health += 10;
				self->FriendlyTeam->Member3->health += 10;
				slog("Water Mage used Mega Heal");
				gfc_sound_play(self->Audio3, 0, 1, 2, -1);
				EndTurn(self);
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

		if (self->TargetMode == Shop)
		{
			Shopping(self);
		}

		//When you have a target and it's an enemy, attack it
		if (self->target != NULL && self->target->EntType == Enemy)
		{
			if (keys[SDL_SCANCODE_1])
			{
				RockThrow(self, self->target);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				slog("Earth Mage Shields themselves");
				self->ShieldHP += 30;
				self->mana -= 40;
				gfc_sound_play(self->Audio2, 0, 1, 2, -1);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				self->ShieldHP += 40;
				self->health += 25;
				self->mana -= 60;
				slog("Earth mages uses Iron Will");
				gfc_sound_play(self->Audio3, 0, 1, 2, -1);
				EndTurn(self);
			}
		}

		//Once in enemy targetting mode, pick an enemy 1 - 3
		SelectEnemyMember(self);
		PickTargetType(self);
	}
}

void WindMage_Think(Entity *self)
{
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_9])
	{
		self->TargetTeam->Member1->health -= 999;
		self->TargetTeam->Member2->health -= 999;
		self->TargetTeam->Member3->health -= 999;
		self->TargetTeam->deaths += 15;
		slog("Team wiped");
		SDL_Delay(150);
	}

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

		if ( self->TargetMode == Shop)
		{
			Shopping(self);
		}

		//When you have a target and it's an enemy, attack it
		if (self->target != NULL && self->target->EntType == Enemy)
		{
			if (keys[SDL_SCANCODE_1])
			{

				gfc_sound_play(self->Audio1, 0, 0.5, 2, -1);
				Gust(self, self->target);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_2])
			{
				//Do Move 2
				slog("Wind Mage uses Whirlwind");
				Whirlwind(self);
				gfc_sound_play(self->Audio2, 0, 1, 2, -1);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_3])
			{
				//Do Move 3
				slog("Wind mage uses plunder");
				int random = gfc_random() * 5;
				slog("%d", random);
				
				if (random == 0)
				{
					slog("Sucks to suck you got nothing boi");
					self->mana += 15;
				}
				else if (random == 1)
				{
					slog("You found a health pot");
					self->Inventory->ItemSlot1->quantity += 1;
					self->mana -= 40;
				}
				else if (random == 2)
				{
					slog("You found a mana pot");
					self->Inventory->ItemSlot2->quantity += 1;
					self->mana -= 40;
				}
				else if (random == 3)
				{
					slog("You found a limit pot");
					self->Inventory->ItemSlot3->quantity += 1;
					self->mana -= 40;
				}
				else if (random == 4)
				{
					slog("You found a mix pot");
					self->Inventory->ItemSlot4->quantity += 1;
					self->mana -= 40;
				}
				else if (random == 5)
				{
					slog("You found a Shield pot");
					self->Inventory->ItemSlot5->quantity += 1;
					self->mana -= 40;
				}
				gfc_sound_play(self->Audio3, 0, 1, 2, -1);
				EndTurn(self);
			}
		}

		//Once in enemy targetting mode, pick an enemy 1 - 3
		SelectEnemyMember(self);
		PickTargetType(self);
	}
}

void IceMage_Think(Entity *self)
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

		if ( self->TargetMode == Shop)
		{
			Shopping(self);
		}

		//When you have a target and it's an enemy, attack it
		if (self->target != NULL && self->target->EntType == Enemy)
		{
			if (keys[SDL_SCANCODE_1])
			{
				IceSpike(self, self->target);
				gfc_sound_play(self->Audio1, 0, 1, 2, -1);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_2])
			{
				Blizzard(self);
				gfc_sound_play(self->Audio2, 0, 1, 2, -1);
				EndTurn(self);
			}

			if (keys[SDL_SCANCODE_3])
			{
				AbsZero(self, self->target);
				gfc_sound_play(self->Audio3, 0, 1, 2, -1);
				EndTurn(self);
			}
		}

		//Once in enemy targetting mode, pick an enemy 1 - 3
		SelectEnemyMember(self);
		PickTargetType(self);
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

	team->Member1 = wind_mage_spawn();
	team->Member2 = water_mage_spawn();
	team->Member3 = earth_mage_spawn();

	team->Inventory = InventorySpawn();
	team->gold = 200;

	team->Member1->gold = team->gold;
	team->Member2->gold = team->gold;
	team->Member3->gold = team->gold;

	team->Member1->Inventory = team->Inventory;
	team->Member2->Inventory = team->Inventory;
	team->Member3->Inventory = team->Inventory;

	team->Member1->FriendlyTeam = team;
	team->Member2->FriendlyTeam = team;
	team->Member3->FriendlyTeam = team;

	//Biome Setting here
	team->Biome = FireTemple;

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
	if (self->InventoryLock = 1)
	{
		slog("Inventory Disabled !");
		self->target = NULL;
		self->TargetMode = Default;
	}

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
		slog("%i", self->target->health);
		slog("Mage Target Enemy 1");
		SDL_Delay(500);
	}

	if (keys[SDL_SCANCODE_2] && self->target == NULL && self->TargetMode == EnemyT)
	{
		self->target = self->TargetTeam->Member2;
		slog("Mage Target Enemy 2");
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_3] && self->target == NULL && self->TargetMode == EnemyT)
	{
		self->target = self->TargetTeam->Member3;
		slog("Mage Target Enemy 3");
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
		slog("Target clear and mode clear");
	}
}

void Shopping(Entity *self)
{
	if (keys[SDL_SCANCODE_1] && self->target != NULL && self->TargetMode == Shop)
	{
		self->Inventory->ItemSlot1->quantity += 1;
		self->gold -= self->target->gold;
		slog("%i", self->gold);
		self->TurnActive = 0;
		self->TurnComplete = 1;
		self->target = NULL;
		self->TargetMode = Default;
		slog("You purchased HP");
		SDL_Delay(500);
	}

	if (keys[SDL_SCANCODE_1] && self->target == NULL && self->TargetMode == Shop)
	{
		self->target = self->TargetTeam->Member1;
		//slog("%i", self->target->health);
		slog("Mage Target HP");
		SDL_Delay(500);
	}

	if (keys[SDL_SCANCODE_2] && self->target != NULL && self->TargetMode == Shop)
	{
		self->Inventory->ItemSlot2->quantity += 1;
		self->gold -= self->target->gold;
		slog("%i", self->gold);
		self->TurnActive = 0;
		self->TurnComplete = 1;
		self->target = NULL;
		self->TargetMode = Default;
		slog("You purchased MP");
		SDL_Delay(500);
	}

	if (keys[SDL_SCANCODE_2] && self->target == NULL && self->TargetMode == Shop)
	{
		self->target = self->TargetTeam->Member2;
		slog("Mage Target Mana Potion");
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_3] && self->target != NULL && self->TargetMode == Shop)
		{
			self->Inventory->ItemSlot3->quantity += 1;
			self->gold -= self->target->gold;
			slog("%i", self->gold);
			self->TurnActive = 0;
			self->TurnComplete = 1;
			self->target = NULL;
			self->TargetMode = Default;
			slog("You purchased Limit");
			SDL_Delay(500);
		}

	if (keys[SDL_SCANCODE_3] && self->target == NULL && self->TargetMode == Shop)
	{
		self->target = self->TargetTeam->Member3;
		slog("Mage Target Limit");

		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_4] && self->target != NULL && self->TargetMode == Shop)
	{
		self->Inventory->ItemSlot4->quantity += 1;
		self->gold -= self->target->gold;
		slog("%i", self->gold);
		self->TurnActive = 0;
		self->TurnComplete = 1;
		self->target = NULL;
		self->TargetMode = Default;
		slog("You purchased Mix");
		SDL_Delay(500);
	}

	if (keys[SDL_SCANCODE_4] && self->target == NULL && self->TargetMode == Shop)
	{
		self->target = self->TargetTeam->Member4;
		slog("Mage Target Mix Potion");
		SDL_Delay(350);
	}

	if (keys[SDL_SCANCODE_5] && self->target != NULL && self->TargetMode == Shop)
	{
		self->Inventory->ItemSlot5->quantity += 1;
		self->gold -= self->target->gold;
		slog("%i", self->gold);
		self->TurnActive = 0;
		self->TurnComplete = 1;
		self->target = NULL;
		self->TargetMode = Default;
		slog("You purchased Shield Potion");
		SDL_Delay(500);
	}

	if (keys[SDL_SCANCODE_5] && self->target == NULL && self->TargetMode == Shop)
	{
		self->target = self->TargetTeam->Member5;
		slog("Mage Target Shield Potion");
		SDL_Delay(350);
	}

	
	
}

void EndTurn(Entity *self)
{
	self->TurnActive = 0;
	self->TurnComplete = 1;
	self->target = NULL;
	self->TargetMode = Default;
	self->InventoryLock = 0;
	slog("Mage Turn End");
	SDL_Delay(350);
}

void SkillCheck(Entity *self, int Skill)
{
	if (Skill == 1)
	{
		if (self->SkillEXP1 >= 20 && self->SkillEXP1 < 50)
		{
			self->SkillLevel1 = 2;
			self->SkillBoost = 10;
			self->ManaReduction = 3;
		}
		if (self->SkillEXP1 >= 50 && self->SkillEXP1 < 100)
		{
			self->SkillLevel1 = 3;
			self->SkillBoost = 15;
			self->ManaReduction = 6;
		}
		if (self->SkillEXP1 >= 100 && self->SkillEXP1 < 150)
		{
			self->SkillLevel1 = 4;
			self->SkillBoost = 20;
			self->ManaReduction = 10;
		}
		if (self->SkillEXP1 >= 150)
		{
			self->SkillLevel1 = 5;
			self->SkillBoost = 30;
			self->ManaReduction = 20;
		}
	}
	if (Skill == 2)
	{
		if (self->SkillEXP2 >= 20 && self->SkillEXP2 < 50)
		{
			self->SkillLevel2 = 2;
			self->SkillBoost2 = 10;
			self->ManaReduction2 = 3;
		}
		if (self->SkillEXP2 >= 50 && self->SkillEXP2 < 100)
		{
			self->SkillLevel2 = 3;
			self->SkillBoost2 = 15;
			self->ManaReduction2 = 6;
		}
		if (self->SkillEXP2 >= 100 && self->SkillEXP2 < 150)
		{
			self->SkillLevel2 = 4;
			self->SkillBoost2 = 20;
			self->ManaReduction2 = 10;
		}
		if (self->SkillEXP2 >= 150)
		{
			self->SkillLevel2 = 5;
			self->SkillBoost2 = 30;
			self->ManaReduction2 = 20;
		}
	}
	if (Skill == 3)
	{
		if (self->SkillEXP3 >= 20 && self->SkillEXP3 < 50)
		{
			self->SkillLevel3 = 2;
			self->SkillBoost3 = 10;
			self->ManaReduction3 = 3;

		}
		if (self->SkillEXP3 >= 50 && self->SkillEXP3 < 100)
		{
			self->SkillLevel3 = 3;
			self->SkillBoost3 = 15;
			self->ManaReduction3 = 6;
		}
		if (self->SkillEXP3 >= 100 && self->SkillEXP3 < 150)
		{
			self->SkillLevel3 = 4;
			self->SkillBoost3 = 20;
			self->ManaReduction3 = 10;
		}
		if (self->SkillEXP3 >= 150)
		{
			self->SkillLevel3 = 5;
			self->SkillBoost3 = 30;
			self->ManaReduction3 = 20;
		}
	}

}

void MasteryCheck(Entity *self, int SkillNum)
{
	//More damage and less mana
	if (SkillNum == 1)
	{

	}

	if (SkillNum == 2)
	{
		
	}

	if (SkillCheck == 3)
	{
		int Level = self->SkillLevel3;
	}

	if (SkillCheck == 4)
	{
		int Level = self->SkillLevel4;
	}
	
	if (SkillCheck == 5)
	{
		int Level = self->SkillLevel5;
	}

}

void Fireball(Entity *self, Entity *target)
{
	//Do Move 1
	slog("Fire Mage used Fireball");
	gfc_sound_play(self->Audio1, 0, 1, 2, -1);

	if (target->ElementType == Fire || target->ElementType == Water)
	{
		target->health = (target->health - (10 * self->DoubleDMG) - self->SkillBoost);
		self->DoubleDMG = 1;
		slog("Reduced Damage, Fire on Fire");
	}

	if (target->ElementType == Wind || target->ElementType == Earth)
	{
		target->health = (target->health - (20 * self->DoubleDMG) - self->SkillBoost);
		self->DoubleDMG = 1;
	}

	if (target->ElementType == Ice)
	{
		target->health = (target->health - (30 * self->DoubleDMG) - self->SkillBoost);
		self->DoubleDMG = 1;
	}
	self->mana += self->ManaReduction;
	self->SkillEXP1 += 5;
	//EndTurn(self);
}

void FlameBreath(Entity *self)
{
	slog("Fire mage used Flame Breath");
	self->mana -= 25;

	Entity *T1 = self->target->FriendlyTeam->Member1;
	Entity *T2 = self->target->FriendlyTeam->Member2;
	Entity *T3 = self->target->FriendlyTeam->Member3;

	Fireball(self, T1);
	Fireball(self, T2);
	Fireball(self, T3);

	self->mana += self->ManaReduction2;
	self->SkillEXP2 += 5;
	//EndTurn(self);
}

void Splash(Entity *self, Entity *target)
{
	//Do Move 1
	slog("Water Mage used Splash");
	gfc_sound_play(self->Audio1, 0, 1, 2, -1);
	if (target->ElementType == Water || target->ElementType == Ice)
	{
		target->health -= (10 + self->SkillBoost); 
		slog("Reduced damage");
	}

	if (target->ElementType == Wind || target->ElementType == Earth)
	{
		target->health -= (15 + self->SkillBoost);
	}

	if (target->ElementType == Fire)
	{
		target->health -= (20 + self->SkillBoost);
		slog("Type Advantage");
	}

	self->mana -= 10;
	self->mana += self->ManaReduction; 
	self->SkillEXP1 += 5;
	//EndTurn(self);
}

void RockThrow(Entity *self, Entity *target)
{
	//Do Move 1
	slog("Earth Mage used Rock Throw");
	gfc_sound_play(self->Audio1, 0, 1, 2, -1);

	if (target->ElementType == Wind || target->ElementType == Earth)
	{
		target->health -= 10;
	}

	if (target->ElementType == Water || target->ElementType == Ice)
	{
		target->health -= 15;
	}

	if (target->ElementType == Fire)
	{
		target->health -= 20;
	}
	
	self->mana -= 15;
	self->mana += self->ManaReduction;
	self->SkillEXP1 += 5;
}

void IceSpike(Entity *self, Entity *target)
{
	//Do Move 1
	slog("Ice Mage used Ice Spike");

	if (target->ElementType == Fire || target->ElementType == Ice)
	{
		target->health -= 10; 
	}

	if (target->ElementType == Wind || target->ElementType == Water)
	{
		target->health -= 15;
	}

	if (target->ElementType == Earth)
	{
		target->health -= 20; 
	}

	self->mana -= 15;
	self->mana += self->ManaReduction;
	self->SkillEXP1 += 5;
}

void Blizzard(Entity *self)
{
	slog("Ice Mage used Blizzard");
	self->mana -= 30;

	Entity *T1 = self->target->FriendlyTeam->Member1;
	Entity *T2 = self->target->FriendlyTeam->Member2;
	Entity *T3 = self->target->FriendlyTeam->Member3;

	IceSpike(self, T1);
	IceSpike(self, T2);
	IceSpike(self, T3);

	self->mana += self->ManaReduction2;
	self->SkillEXP2 += 5;
}

void AbsZero(Entity *self, Entity *target)
{
	//Do Move 3
	slog("Ice Mage: So Cold it burns.");
	if (target->ElementType == Fire || target->ElementType == Ice)
	{
		target->health -= 40;
	}

	if (target->ElementType == Wind || target->ElementType == Water)
	{
		target->health -= 45;
	}

	if (target->ElementType == Earth)
	{
		target->health -= 60;
	}

	self->mana -= 60;
	self->mana += self->ManaReduction3;
	self->SkillEXP3 += 5;
}

void Gust(Entity *self, Entity *target)
{
	//Do Move 1
	slog("Wind Mage used Gust");
	if (target->ElementType == Earth || target->ElementType == Ice)
	{
		target->health -= 15;
	}

	if (target->ElementType == Water || target->ElementType == Wind)
	{
		target->health -= 20;
	}

	if (target->ElementType == Fire)
	{
		target->health -= 25;
	}
	self->mana -= 10;
	self->mana += self->ManaReduction;
	self->SkillEXP1 += 5;
}

void Whirlwind(Entity *self)
{
	self->mana -= 30;

	Entity *T1 = self->target->FriendlyTeam->Member1;
	Entity *T2 = self->target->FriendlyTeam->Member2;
	Entity *T3 = self->target->FriendlyTeam->Member3;

	Gust(self, T1);
	Gust(self, T2);
	Gust(self, T3);
	self->mana += self->ManaReduction2;
	self->SkillEXP2 += 5;
}