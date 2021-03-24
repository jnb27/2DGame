#include <stdlib.h>
#include "simple_logger.h"

#include "entity.h"

typedef struct
{
	Entity *entity_list;
	Uint32  max_entities;
}EntityManager;

static EntityManager entity_manager = { 0 };

void entity_manager_init(Uint32 max_entities)
{
	if (max_entities == 0)
	{
		slog("cannot allocate 0 entities!");
		return;
	}
	if (entity_manager.entity_list != NULL)
	{
		entity_manager_free();
	}
	entity_manager.entity_list = (Entity *)gfc_allocate_array(sizeof (Entity), max_entities);
	if (entity_manager.entity_list == NULL)
	{
		slog("failed to allocate entity list!");
		return;
	}
	entity_manager.max_entities = max_entities;
	atexit(entity_manager_free);
	slog("entity system initialized");
}

void entity_manager_free()
{
	if (entity_manager.entity_list != NULL)
	{
		free(entity_manager.entity_list);
	}
	memset(&entity_manager, 0, sizeof(EntityManager));
	slog("entity system closed");
}

void entity_update(Entity *self)
{
	if (!self)return;
	// DO ANY GENERIC UPDATE CODE
	vector2d_add(self->position, self->position, self->velocity);
	self->frame += self->frameRate;
	if (self->frame >= self->frameCount)self->frame = 0;
	// IF THERE IS A CUSTOM UPDATE, DO THAT NOW
	if (self->update)self->update(self);
}

void entity_manager_update_entities()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse == 0)continue;
		entity_update(&entity_manager.entity_list[i]);

		int x;
		for (x = 0; x < entity_manager.max_entities; x++)
		{
			if (&entity_manager.entity_list[x] == &entity_manager.entity_list[i])continue;

			if (!&entity_manager.entity_list[x] || !&entity_manager.entity_list[i])
			{
				slog("Im outta here");
			}

			if (checkCollision(&entity_manager.entity_list[x], &entity_manager.entity_list[i]) == 1)
			{
				slog("Yeah it works");
			}
		}
	}
}

void entity_think(Entity *self)
{
	if (!self)return;
	if (!self->think)return; 
	self->think(self);
}

void entity_manager_think_all()
{
	int i;
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse == 0)continue;
		entity_think(&entity_manager.entity_list[i]);
	}
}

void entity_manager_draw_entities()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse == 0)continue;
		entity_draw(&entity_manager.entity_list[i]);
	}
}


Entity *entity_new()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return NULL;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse)continue;// someone else is using this one
		memset(&entity_manager.entity_list[i], 0, sizeof(Entity));
		entity_manager.entity_list[i]._inuse = 1;
		return &entity_manager.entity_list[i];
	}
	slog("no free entities available");
	return NULL;
}

void entity_free(Entity *ent)
{
	if (!ent)
	{
		slog("cannot free a NULL entity");
		return;
	}
	gf2d_sprite_free(ent->sprite);
	ent->sprite = NULL;
	ent->_inuse = 0;
}

void entity_draw(Entity *ent)
{
	if (!ent)
	{
		slog("cannot draww a NULL entity");
		return;
	}
	if (ent->draw)
	{
		ent->draw(ent);
	}
	else
	{
		if (ent->sprite == NULL)
		{
			return;// nothing to draw
		}
		gf2d_sprite_draw(
			ent->sprite,
			ent->position,
			NULL,
			NULL,
			&ent->rotation,
			NULL,
			NULL,
			(Uint32)ent->frame);
	}
}

void test_ent()
{
	Entity *ent;
	ent = entity_new();
	if (!ent)
	{
		slog("failed to create test");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/enemies/mage-2-122x110.png", 122, 110, 4);
	ent->frameRate = 0.1;
	ent->frameCount = 8;
	//ent->update = player_update;
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	ent->position.x = 240;
	ent->position.y = 240;

	ent->ActionPoints = 0;
	ent->health = 100;
	ent->mana = 100;
	ent->limit = 0;
	ent->TurnActive = 0;

	return ent;
}


int checkCollision(Entity *self, Entity *other)
{
	float distance_x = self->position.x - other->position.x;
	float distance_y = self->position.y - other->position.y;

	if (self->radius == 0 || other->radius == 0) return 0;

	float radii_sum = self->radius + other->radius;

	if ((distance_x * distance_x) + (distance_y * distance_y) <= (radii_sum * radii_sum)) return 1;

	return 0;
}

void AdjustPositions(Entity *self)
{
	self->Member1->position.y = 480;
	self->Member2->position.y = 360;
	self->Member3->position.y = 240;
}
/*eol@eof*/