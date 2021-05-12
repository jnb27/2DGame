#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf2d_sprite.h"
#include "gfc_audio.h"

enum EntityType
{
	Player,
	Party,
	Enemy
};

enum ItemType
{
	HealthPotion,
	ManaPotion,
	LimitBreak
};

enum Element
{
	Fire,
	Water,
	Earth,
	Wind,
	Ice
};

enum TargetSys
{
	Team,
	EnemyT, 
	Default,
	Shop
};

enum Biomes
{
	FireTemple,
	IceTemple,
	WaterTemple,
	EarthTemple,
	WindTemple
};

typedef struct Entity_s
{
	Bool       _inuse;
	Vector2D    position;
	Vector2D    velocity;
	Vector3D    rotation; //(x,y) = rotation center, z = degrees of rotation
	Sprite     *sprite;
	float       frame;
	float       frameRate;
	int         frameCount;

	int			health;
	int			mana;
	int			limit;
	int			ElementType;
	int			Attack;
	int			Defense;
	int			ShieldHP;
	int			DoubleDMG;

	int			deaths;
	int			InventoryLock;
	int			quantity;
	int			gold;

	int			Biome;

	int			SkillLevel1;
	int			SkillLevel2;
	int			SkillLevel3;
	int			SkillLevel4;
	int			SkillLevel5;

	int			SkillBoost;
	int			SkillBoost2;
	int			SkillBoost3;

	int			ManaReduction;
	int			ManaReduction2;
	int			ManaReduction3;

	int			SkillEXP1;
	int			SkillEXP2;
	int			SkillEXP3;
	int			SkillEXP4;
	int			SkillEXP5;

	Sound		*Audio1;
	Sound		*Audio2;
	Sound		*Audio3;

	struct		Entity_s *Inventory;
	struct		Entity_s *ItemSlot1;
	struct		Entity_s *ItemSlot2;
	struct		Entity_s *ItemSlot3;
	struct		Entity_s *ItemSlot4;
	struct		Entity_s *ItemSlot5;

	struct      Entity_s *ActiveDrop1;
	struct      Entity_s *ActiveDrop2;
	struct      Entity_s *ActiveDrop3;
	struct      Entity_s *ActiveDrop4;
	struct      Entity_s *ActiveDrop5;


	struct		Entity_s *Member1;
	struct		Entity_s *Member2;
	struct		Entity_s *Member3;
	struct		Entity_s *Member4;
	struct		Entity_s *Member5;

	struct		Entity_s *TargetTeam;
	struct		Entity_s *FriendlyTeam;

	int			EntType;
	int			TargetMode;
	int			TurnComplete;
	int			TurnActive;  //Maybe have a check that if all entities in the list have TurnActive mechanic in the game loop they'll do different things. 
	int			ActionPoints; //Maybe something to turn on and off turns
	struct		Entity_s *target; 
	int			radius; //Using this for collision detection

	void(*update)(struct Entity_s *self);
	void(*think)(struct Entity_s *self);
	void(*draw)(struct Entity_s *self);
	void(*free)(struct Entity_s *self);
	void       *data;
}Entity;

/**
* @brief initialize internal entity management system
* @param max_entities how many concurrent entities to support
*/
void entity_manager_init(Uint32 max_entities);

/**
* @brief calls update function on all entities
*/
void entity_manager_update_entities();


/**
* @brief call draw on all entities
*/
void entity_manager_draw_entities();


/**
* @brief free all entities in the system and destroy entity manager
*/
void entity_manager_free();

/**
* @brief allocate an entity, initialize it to zero and return a pointer to it
* @return NULL on error (see logs) or a pointer to an initialized entity.
*/
Entity *entity_new();

/**
* @brief frees provided entity
* @param ent the entity to free
*/
void entity_free(Entity *ent);

/**
* @brief draws an entity to the current render frame
* @param ent the entity to draw
*/
void entity_draw(Entity *ent);

void entity_manager_think_all();

void test_ent();

void AdjustPositions(Entity *self);

#endif