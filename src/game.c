#include <SDL.h>

#include <math.h>

#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

#include "entity.h"
#include "player.h"
#include "level.h"
#include "Mage.h"
#include "Monster.h"
#include "Item.h"
#include "gfc_audio.h"

void GodHelpMe(Entity *self, Entity *pic);
void GodHelpMe2(Entity *self, Entity *pic);
void GodHelpMe3(Entity *self, Entity *pic);

int main(int argc, char * argv[])
{
	/*variable declarations*/
	int done = 0;
	int MenuActive = 0;
	int levelJump1 = 0;
	int levelJump2 = 0;
	int levelJump3 = 0;
	
	const Uint8 * keys;
	Level *level;
	//Entity *playerT;
	Entity *team1;
	Entity *team2;
	//Entity *PM1HP;

	int mx, my;
	float mf = 0;
	Sprite *mouse;
	Entity *PM1;
	Entity *PM2;
	Entity *PM3;
	int Bossflip = 0;
	Vector4D mouseColor = { 255, 100, 255, 200 };

	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"gf2d",
		1200,
		720,
		1200,
		720,
		vector4d(0, 0, 0, 255),
		0);
	gf2d_graphics_set_frame_delay(16);
	gfc_audio_init(256, 16, 4, 4, 1, 1);
	gf2d_sprite_init(1024);
	entity_manager_init(300);


	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	Sound *BGM = gfc_sound_load("music/wisdom.mp3", 0.5, 1);
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	level = level_load("levels/exampleLevel.json");
	slog("%d", level->Biome);

	PM1 = entity_new();
	PM1->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-100.png");
	PM1->position.y = 660;

	PM2 = entity_new();
	PM2->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-100.png");
	PM2->position.y = 660;
	PM2->position.x = 120;

	PM3 = entity_new();
	PM3->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-100.png");
	PM3->position.y = 660;
	PM3->position.x = 240;


	//playerT = player_spawn(vector2d(100, 100));
	//test_ent();
	//earth_mage_spawn();
	team1 = Mage_Team();
	team1->Biome = 1;
	//team2 = BossTeam();
	team2 = Monster_Team();
	team2->Biome = 1;

	team1->TurnActive = 1;
	team1->TargetTeam = team2;
	team2->TargetTeam = team1;

	//water_monster_spawn();
	gfc_sound_play(BGM, 0, 1, 1, -1);

	/*main game loop*/
	while (!done)
	{
		if (MenuActive == 1)
		{

		}
		else{

			SDL_PumpEvents();   // update SDL's internal event structures
			keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
			/*update things here*/
			SDL_GetMouseState(&mx, &my);
			mf += 0.1;
			if (mf >= 16.0)mf = 0;

			if (team2->deaths >= 45 && Bossflip == 0)
			{

				team2 = BossTeam();
				team1->TargetTeam = team2;
				team2->TargetTeam = team1;
				Bossflip = 1;
			}

			if (team2->deaths >= 10 && team2->deaths <= 20 && levelJump1 == 0)
			{
				//level_free(level);
				//Air
				level = level_load("levels/exampleLevel2.json");
				levelJump1 = 1;
				team1->Biome = 2;
			}

			if (team2->deaths >= 21 && team2->deaths <= 30 && levelJump2 == 0)
			{
				//level_free(level);
				//Fire
				level = level_load("levels/exampleLevel3.json");
				levelJump2 = 1;
				team1->Biome = 3;
			}

			if (team2->deaths >= 31 && team2->deaths <= 40 && levelJump3 == 0)
			{
				//level_free(level);
				//Earth
				level = level_load("levels/exampleLevel4.json");
				levelJump3 = 1;
				team1->Biome = 4;
			}

			if (keys[SDL_SCANCODE_J] && Bossflip == 1)
			{
				entity_free(team2->Member1);
				team2 = BossTeam();
				team1->TargetTeam = team2;
				team2->Member1->think = BossThink2;

			}

			if (keys[SDL_SCANCODE_I])
			{
				//Now we spawn the item shop

				//First clean up anything that may be lying around. 
				entity_free(team2->Member1);
				entity_free(team2->Member2);
				entity_free(team2->Member3);

				if (team2->Member4 != NULL)
				{
					entity_free(team2->Member4);
				}

				if (team2->Member5 != NULL)
				{
					entity_free(team2->Member5);
				}


				team1->Member1->target = NULL;
				team1->Member2->target = NULL;
				team1->Member3->target = NULL;

				team1->Member1->TargetMode = Shop;
				team1->Member2->TargetMode = Shop;
				team1->Member3->TargetMode = Shop;


				team2->Member1 = ShopHP();
				team2->Member2 = ShopMana();
				team2->Member3 = ShopLimit();
				team2->Member4 = ShopMix();
				team2->Member5 = ShopShield();
			}

			GodHelpMe(team1, PM1);
			GodHelpMe2(team1, PM2);
			GodHelpMe3(team1, PM3);


			entity_manager_think_all();
			entity_manager_update_entities();

			gf2d_graphics_clear_screen();// clears drawing buffers
			// all drawing should happen betweem clear_screen and next_frame
			//backgrounds drawn first

			level_draw(level);


			entity_manager_draw_entities();

			if (PM1 == NULL)
			{
				slog("Pics broke");
			}

			//UI elements last
			//PM1 = gf2d_sprite_load_image("images/Member1Card.png");
			//gf2d_sprite_draw(PM1, vector2d(300, 300), NULL,NULL,NULL,NULL, Vector4d(255,255,255, 0 ), 1);
			gf2d_sprite_draw(
				mouse,
				vector2d(mx, my),
				NULL,
				NULL,
				NULL,
				NULL,
				&mouseColor,
				(int)mf);
			gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

			if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
			        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
		}
	}
	slog("---==== END ====---");
	return 0;
}


//I am not proud of this method I used to get HP text going, but when the going gets rough life finds a way. 
void GodHelpMe(Entity *self, Entity *pic)
{
	switch (self->Member1->health)
	{
		case 100:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-100.png");
			break;
		case 95:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-95.png");
			break;
		case 90:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-90.png");
			break;
		case 85:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-85.png");
			break;
		case 80:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-80.png");
			break;
		case 75:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-75.png");
			break;
		case 70:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-70.png");
			break;
		case 65:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-65.png");
			break;
		case 60:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-60.png");
			break;
		case 55:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-55.png");
			break;
		case 50:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-50.png");
			break;
		case 45:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-45.png");
			break;
		case 40:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-40.png");
			break;
		case 35:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-35.png");
			break;
		case 30:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-30.png");
			break;
		case 25:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-25.png");
			break;
		case 20:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-20.png");
			break;
		case 15:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-15.png");
			break;
		case 10:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-10.png");
			break;
		case 5:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-5.png");
			break;
		case 0:
			pic->sprite = gf2d_sprite_load_image("images/Unholy/PM1/PM1-0.png");
			break;
	}
}

void GodHelpMe2(Entity *self, Entity *pic)
{
	switch (self->Member2->health)
	{
	case 100:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-100.png");
		break;
	case 95:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-95.png");
		break;
	case 90:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-90.png");
		break;
	case 85:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-85.png");
		break;
	case 80:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-80.png");
		break;
	case 75:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-75.png");
		break;
	case 70:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-70.png");
		break;
	case 65:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-65.png");
		break;
	case 60:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-60.png");
		break;
	case 55:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-55.png");
		break;
	case 50:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-50.png");
		break;
	case 45:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-45.png");
		break;
	case 40:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-40.png");
		break;
	case 35:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-35.png");
		break;
	case 30:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-30.png");
		break;
	case 25:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-25.png");
		break;
	case 20:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-20.png");
		break;
	case 15:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-15.png");
		break;
	case 10:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-10.png");
		break;
	case 5:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-5.png");
		break;
	case 0:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM2/PM2-0.png");
		break;
	}
}

void GodHelpMe3(Entity *self, Entity *pic)
{
	switch (self->Member3->health)
	{
	case 100:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-100.png");
		break;
	case 95:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-95.png");
		break;
	case 90:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-90.png");
		break;
	case 85:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-85.png");
		break;
	case 80:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-80.png");
		break;
	case 75:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-75.png");
		break;
	case 70:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-70.png");
		break;
	case 65:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-65.png");
		break;
	case 60:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-60.png");
		break;
	case 55:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-55.png");
		break;
	case 50:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-50.png");
		break;
	case 45:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-45.png");
		break;
	case 40:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-40.png");
		break;
	case 35:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-35.png");
		break;
	case 30:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-30.png");
		break;
	case 25:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-25.png");
		break;
	case 20:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-20.png");
		break;
	case 15:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-15.png");
		break;
	case 10:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-10.png");
		break;
	case 5:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-5.png");
		break;
	case 0:
		pic->sprite = gf2d_sprite_load_image("images/Unholy/PM3/PM3-0.png");
		break;
	}
}



/*eol@eof*/