#include "simple_logger.h"
#include "Monster.h"

const Uint8 *keys;
void BossTeamThink(Entity *self);
void BossThink(Entity *self);

void BossMoveSet1(Entity *self);
void BossMoveSet2(Entity *self);


Entity *Boss1_Spawn()
{
	Entity *monster;
	monster = entity_new();
	if (!monster)
	{
		slog("failed to create test");
		return NULL;
	}
	monster->sprite = gf2d_sprite_load_all("images/enemies/andromalius-57x88.png", 57, 88, 8);
	monster->frameRate = 0.1;
	monster->frameCount = 24;
	monster->rotation.x = 64;
	monster->rotation.y = 64;
	monster->position.x = 600;
	monster->position.y = 240;

	monster->think = BossThink2;
	monster->EntType = Enemy;
	monster->ElementType = Fire;
	monster->ActionPoints = 0;
	monster->health = 450;
	monster->mana = 100;
	monster->limit = 0;
	monster->TurnActive = 0;
	monster->TurnComplete = 0;


	return monster;
}


Entity *BossTeam()
{
	Entity *BossTeam;
	BossTeam = entity_new();

	if (!BossTeam)
	{
		slog("Failed to spawn boss");
		return;
	}

	BossTeam->think = BossTeamThink;
	BossTeam->TurnActive = 0;
	BossTeam->TurnComplete = 0;

	BossTeam->Member1 = Boss1_Spawn();
	BossTeam->Member2 = BossTeam->Member1;
	BossTeam->Member3 = BossTeam->Member1;

	BossTeam->Member1->FriendlyTeam = BossTeam;
	BossTeam->Member2->FriendlyTeam = BossTeam;
	BossTeam->Member3->FriendlyTeam = BossTeam;

	return BossTeam;
}

void BossTeamThink(Entity *self)
{
	if (!self)return;

	self->Member1->TargetTeam = self->TargetTeam;
	self->Member2->TargetTeam = self->TargetTeam;
	self->Member3->TargetTeam = self->TargetTeam;

	if (self->TurnActive == 1 && self->TurnComplete <= 2)
	{
		//Allowed to do stuff
		self->Member1->TurnActive = 1;

	}
	self->TurnComplete += 1;
	if (self->TurnActive == 1 && self->TurnComplete >= 3)
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

void BossThink(Entity *self)
{
	if (!self)return;

	if (self->health == 0)
	{
		entity_free(self);
	}

	if (self->TurnActive == 1 && self->TurnComplete <= 2)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		int rando = (gfc_random() * 3) + 1;
		slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->TargetTeam->Member1;
			BossMoveSet1(self);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->TargetTeam->Member2;
			BossMoveSet1(self);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->TargetTeam->Member3;
			BossMoveSet1(self);
			SDL_Delay(200);
		}
	}
}

void BossThink2(Entity *self)
{
	if (!self)return;

	if (self->health == 0)
	{
		entity_free(self);
	}

	if (self->TurnActive == 1 && self->TurnComplete < 1)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		int rando = (gfc_random() * 3) + 1;
		slog("%i", rando);

		if (rando == 1)
		{
			self->target = self->TargetTeam->Member1;
			BossMoveSet2(self);
			SDL_Delay(200);
		}
		else if (rando == 2)
		{
			self->target = self->TargetTeam->Member2;
			BossMoveSet2(self);
			SDL_Delay(200);
		}
		else if (rando == 3)
		{
			self->target = self->TargetTeam->Member3;
			BossMoveSet2(self);
			SDL_Delay(200);
		}
	}
}

void BossDrain(Entity *self)
{
	self->target->health -= 20;
	self->target->mana -= 10;
	self->health += 30;
	self->mana += 30;
	self->TurnActive = 0;
	self->TurnComplete += 1;
	slog("Boss casts drain Team member 1. Team Member Health:");
	slog("%i", self->target->health);
}

void BossLock(Entity *self)
{
	self->target->InventoryLock = 1;
	self->TurnActive = 0;
	self->TurnComplete += 1;
	slog("Boss casts Lock. Inventory Disabled for one turn");
}

void BossCleave(Entity *self)
{
	self->target->FriendlyTeam->Member1->health -= 15;
	self->target->FriendlyTeam->Member2->health -= 15;
	self->target->FriendlyTeam->Member3->health -= 15;

	self->TurnActive = 0;
	self->TurnComplete += 1;
	slog("Cleave, all members are hit");
}

void BossNuke(Entity *self)
{
	self->target->health -= 35;
	self->TurnActive = 0;
	self->TurnComplete += 1;
	slog("Boss uses Punishment. Team Member Health: ");
}

void BossHeal(Entity *self)
{
	self->health += 50;
	self->TurnActive = 0;
	self->TurnComplete += 1;
	slog("Boss uses Greater Restoration");
}

void BossMoveSet1(Entity *self)
{
	int rand2 = (gfc_random() * 3) + 1;

	if (rand2 == 1)
	{
		BossDrain(self);
	}

	if (rand2 == 2)
	{
		BossLock(self);
	}

	if (rand2 == 3)
	{
		BossCleave(self);
	}
}

void BossMoveSet2(Entity *self)
{
	int rand2 = (gfc_random() * 2) + 1;

	if (rand2 == 1)
	{
		BossHeal(self);
	}

	if (rand2 == 2)
	{
		BossNuke(self);
	}
}