#include "simple_logger.h"

#include "player.h"

void player_update(Entity *self);
void player_think(Entity *self);

const Uint8 *keys;

Entity *player_spawn(Vector2D position)
{
	Entity *ent;
	ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the player");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/ed210_top.png", 128, 128, 16);
	vector2d_copy(ent->position, position);
	ent->frameRate = 0.1;
	ent->frameCount = 16;
	ent->update = player_update;
	ent->rotation.x = 64;
	ent->rotation.y = 64;

	ent->ActionPoints = 0;
	ent->health = 100;
	ent->mana = 100;
	ent->limit = 0;
	ent->TurnActive = 0; 
	ent->radius = 1;
	ent->think = player_think;
	
	return ent;
}

void player_think(Entity *self)
{
	if (!self)return;
	if (self->TurnActive == 1)
	{
		if (!self)return;
		keys = SDL_GetKeyboardState(NULL);
		/*if (keys[SDL_SCANCODE_D])
		{
			self->position.x += 10;
			self->TurnActive = 0;
		}*/
		if (keys[SDL_SCANCODE_A])
		{
			self->position.x -= 1;
		}
		if (keys[SDL_SCANCODE_W])
		{
			self->position.y -= 1;
		}
		if (keys[SDL_SCANCODE_S])
		{
			self->position.y += 1;
		}
	}
}


//This kinda works like a think but I need to make sure I know the difference soon
void player_update(Entity *self)
{
	Vector2D aimdir;
	float angle;
	int mx, my;
	if (!self)return;
	SDL_GetMouseState(&mx, &my);
	aimdir.x = mx - (self->position.x + 64);
	aimdir.y = my - (self->position.y + 64);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;

}

/**/