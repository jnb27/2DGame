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


int main(int argc, char * argv[])
{
	/*variable declarations*/
	int done = 0;
	const Uint8 * keys;
	Level *level;
	Entity *playerT;
	Entity *team1;
	Entity *team2; 

	int mx, my;
	float mf = 0;
	Sprite *mouse;
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
	gf2d_sprite_init(1024);
	entity_manager_init(100);


	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	level = level_load("levels/exampleLevel.json");


	//playerT = player_spawn(vector2d(100, 100));
	//test_ent();
	//earth_mage_spawn();
	team1 = Mage_Team();
	team2 = Monster_Team();

	team1->TurnActive = 1;

	//water_monster_spawn();
	


	/*main game loop*/
	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);
		mf += 0.1;
		if (mf >= 16.0)mf = 0;

		//if (keys[SDL_SCANCODE_T])
		//{
		//	if (!playerT)return;
		//	playerT->TurnActive = 1;
		//}

		//if (keys[SDL_SCANCODE_Y])
		//{
		//	if (!playerT)return;
		//	playerT->TurnActive = 0;
		//}

		entity_manager_think_all();
		entity_manager_update_entities();

		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame
		//backgrounds drawn first
		level_draw(level);

		entity_manager_draw_entities();

		//UI elements last
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
		//        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
	}
	slog("---==== END ====---");
	return 0;
}
/*eol@eof*/